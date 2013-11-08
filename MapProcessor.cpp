#include "MapProcessor.h"

void CMapProcessor::swapMap(std::string mapName, MAPSTORAGE location)
{
	//set _currentMap to the proper map -- still need to do this 
}

void CMapProcessor::insertEntity(CEntity * ent, int layer)
{
	_currentMap->insertEntity(ent, layer);
}

void CMapProcessor::process()
{
	if (_currentMap != nullptr)
	{
		_currentMap->checkCollisions();
	}
}

std::unordered_map<std::string, CEntity*> * CMapProcessor::getEntRegistry()
{
	return &_currentMap->_entityRegistry;
}