#include "EventProcessor.h"

CEventProcessor::CEventProcessor(std::list<std::string> globalEvents, std::list<std::string> sysEvents, OIS::ParamList pl)
{
	_eventQueue = new CEventQueue();
	_inputProcessor = new CInputProcessor(pl);
	_mapProcessor = new CMapProcessor();

	for (std::list<std::string>::iterator itr = globalEvents.begin(); itr != globalEvents.end(); itr++)
	{
		std::pair<std::string,bool> pair(*itr, false);
		_globalEvents.insert(pair);
	}

	for (std::list<std::string>::iterator itr = sysEvents.begin(); itr != sysEvents.end(); itr++)
	{
		std::pair<std::string,bool> pair(*itr, false);
		_sysEvents.insert(pair);
	}

}

CEventProcessor::~CEventProcessor()
{
	CEvent * cleaner = nullptr;

	while (cleaner = _eventQueue->popEvent())
	{
		delete cleaner;
		cleaner = nullptr;
	}

	delete _eventQueue;
	_eventQueue = NULL;

	delete _inputProcessor;
	_inputProcessor = nullptr;
	delete _mapProcessor;
	_mapProcessor = nullptr;
}

void CEventProcessor::process()
{
	_inputProcessor->processInput();
	_mapProcessor->process();

	_listen();
	_processQueue();

	//shut off all events
	for (std::unordered_map<std::string,bool>::iterator itr = _globalEvents.begin(); itr != _globalEvents.end(); itr++)
		itr->second = false;
	
}

CMap CEventProcessor::getCurrentMap()
{
	if (_mapProcessor->_currentMap == nullptr)
		return CMap();

	return CMap(*_mapProcessor->_currentMap);
}

void CEventProcessor::setCurrentMap(CMap * map)
{
	_mapProcessor->_currentMap = map;
}

void CEventProcessor::_listen()
{
	//algorithm
	//For each entity
	//	for each global event fired
	//		if entity has an event definition for event
	//			grab its parameters and function
	//			store in event queue
	//	for each local event fired
	//		if entity has an event definition for event
	//			grab its parameters and function
	//			store in event queue


	
	
	std::unordered_map<std::string, CEntity*> * entRegistry = _mapProcessor->getEntRegistry();
	//check collisions
	//_mapProcessor->process();

	//check if any keys were pressed
	_globalEvents["keyPress"] = _inputProcessor->_keyBuffer.size() > 0;
	_globalEvents["keyRelease"] = _inputProcessor->_keyReleasedBuffer.size() > 0;
	_globalEvents["mapStart"] = _mapProcessor->_mapStart;
	_globalEvents["mapEnd"] = _mapProcessor->_mapEnd;
	_globalEvents["mousePress"] = _inputProcessor->_mouseButtonBuffer.size() > 0;

	for (std::unordered_map<std::string, CEntity*>::iterator itr = entRegistry->begin(); itr != entRegistry->end(); itr++)
	{
		if (itr->second->enabled())
		{
			for (std::unordered_map<std::string,bool>::iterator itrMap = _globalEvents.begin(); itrMap != _globalEvents.end(); itrMap++)
			{
				if (itrMap->second)
				{
					//frame event ALWAYS fires
					EvFrame * frame = new EvFrame(itr->second);
					_eventQueue->push(frame);

					if (itrMap->first == "keyPress")
					{
						EvKeyPressed * keyPress = new EvKeyPressed(_inputProcessor->_keyBuffer, itr->second);
						_eventQueue->push(keyPress);
					}
					if(itrMap->first == "mapEnd")
					{
						EvMapEnd * mapEnd = new EvMapEnd(itr->second);
						_eventQueue->push(mapEnd);
					}
					if (itrMap->first ==  "mousePress")
					{
						EvMousePress * mousePress = new EvMousePress(_inputProcessor->_mouseButtonBuffer, itr->second);
						_eventQueue->push(mousePress);
					}
				}
			}
		}
	}

	//now local events
	for (std::unordered_map<std::string, CEntity*>::iterator itr = entRegistry->begin(); itr != entRegistry->end(); itr++)
	{
		//destoy event
		if (itr->second->getDestructionFlag())
		{
			EvDestroy * destroy = new EvDestroy(itr->second);
			_eventQueue->push(destroy);
		}

		//collision events
		if (itr->second->enabled())
		{
			while (itr->second->getCollisionSize() > 0)
			{
				CEntity * collidedWith = (itr->second)->getNextCollision();
				EvCollision * collision = new EvCollision(collidedWith, itr->second);
				_eventQueue->push(collision);
			}
		}
	}

	//check system events last
	std::pair<std::string, MAPSTORAGE> swapMap;

	while (CEntity::getEntCreationSize() > 0)
	{
		CEntCreation creation = CEntity::getNextEntCreator();
		EvCreateEnt * createEnt = new EvCreateEnt(creation, _mapProcessor);
		_eventQueue->push(createEnt);
	}


	if (_murderUs.size() > 0)
	{
		//begin murder process?
		for (std::unordered_map<std::string, CEntity*>::iterator itr = _murderUs.begin(); itr != _murderUs.end(); itr++)
		{
			CEntity * killMe = itr->second;
			EvDestroyEnt * destroy = new EvDestroyEnt(killMe);
			_eventQueue->push(destroy);
		}
		_murderUs.clear();
	}
	while (CEntity::getEntDestructionSize() > 0)
	{
		std::string ent = CEntity::getNextEntDestroyer();

		//locate the entity we need to wreck havoc upon
		CEntity * kickMyAss = _mapProcessor->_currentMap->searchRegistry(ent);

		//we can't do this in one cycel due to the EvDestroy event, so we'll do this on the next cycle.
		//This will also disable the entity to prevent it from doing further things while waiting for the next cycle
		if (kickMyAss != nullptr)
		{
			kickMyAss->markDestruction();
			_murderUs.insert(std::make_pair(kickMyAss->name(), kickMyAss)); //I'LL GET YOU NEXT TIME, GADGET!!!
		}
		
	}

	if (_mapProcessor->_mapEnd)
	{
		EvSwapMap * mapSwap = new EvSwapMap(swapMap.first, swapMap.second, _mapProcessor);
		_eventQueue->push(mapSwap);
		_mapProcessor->_mapEnd = false;
	}
	else if ((swapMap = CEntity::popMapSwaps()).first != "NULL")
	{
		//shit, we've got a map change!
		//at the end of the next cycle, we're going to change maps
		//we can't allow another map swap during that time, so we're going to make that check take priority over this one
		_mapProcessor->_mapEnd = true;
		CEntity::resetMapSwap();
	}
}

void CEventProcessor::_processQueue()
{
	CEvent * event = nullptr;
	while (event = _eventQueue->popEvent())
	{
		event->process();

		//get that shit off the heap as soon as we're done with it
		delete event;
		event = nullptr;
	}
}