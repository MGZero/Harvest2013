#ifndef _EVENTPROCESSOR_H_
#define _EVENTPROCESSOR_H_

#include "CEventQueue.h"
#include "CEntity.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include "InputProcessor.h"
#include "MapProcessor.h"

#include "EvKeyPressed.h"
#include "EvMapEnd.h"
#include "EvMousePress.h"

#include "EvDestroy.h"
#include "EvCreate.h"
#include "EvCollision.h"

#include "EvSwapMap.h"
#include "EvCreateEnt.h"
#include "EvDestroyEnt.h"
#include "EvFrame.h"

class CEventProcessor
{
public:
	CEventProcessor(std::list<std::string> globalEvents, std::list<std::string> sysEvents, OIS::ParamList);
	~CEventProcessor();

	void process();
	inline bool quitGame(){return _inputProcessor->quitGame();}
	CMap getCurrentMap();
	
	//tests only
	void setCurrentMap(CMap * map);


private:
	//no implementation -- do not use
	CEventProcessor(const CEventProcessor &);
	CEventProcessor & operator= (const CEventProcessor &);

	//Hey!
	void _listen();
	void _processQueue();

	CEventQueue * _eventQueue;
	std::unordered_map<std::string, bool> _globalEvents;
	std::unordered_map<std::string, bool> _sysEvents;
	std::unordered_map<std::string, CEntity *> _murderUs;
	CInputProcessor * _inputProcessor;
	CMapProcessor * _mapProcessor;
};

#endif