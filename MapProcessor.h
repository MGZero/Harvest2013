#ifndef MAPPROCESSOR_H
#define MAPPROCESSOR_H

#include "CMap.h"
#include "GraphicsProcessor.h"

class CMapProcessor
{
public:
	CMapProcessor() : _currentMap(nullptr){}
	virtual ~CMapProcessor(){};
	friend class CEventProcessor;

	void process();
	void swapMap(std::string mapName, MAPSTORAGE location);
	void insertEntity(CEntity * ent, int layer);


private:
	CMap * _currentMap;
	std::list<CMap*> _storedMaps;
	bool _mapStart;
	bool _mapEnd;

	std::unordered_map<std::string, CEntity*> * getEntRegistry();
	

};

#endif