#include "EvSwapMap.h"

EvSwapMap::EvSwapMap(std::string map, MAPSTORAGE location, CMapProcessor * mapProcessor) : CEvent()
{
	_parameterList.push_front(map);
	_parameterList.push_front((int)location);
	_sender = nullptr;
	_mapProcessor = mapProcessor;
}

EvSwapMap::~EvSwapMap()
{

}

void EvSwapMap::process()
{
	paramList::iterator itr = _parameterList.begin();

	int location = boost::get<int>(_parameterList.front()); _parameterList.pop_front();
	std::string mapName = boost::get<std::string>(_parameterList.front()); _parameterList.pop_front();
	
	_mapProcessor->swapMap(mapName, (MAPSTORAGE)location);
}