#ifndef EVSWAPMAP_H
#define EVSWAPMAP_H

#include "CEvent.h"
#include "MapProcessor.h"

class EvSwapMap : public CEvent
{
public:
	EvSwapMap(std::string map, MAPSTORAGE location, CMapProcessor * mapProcessor);
	virtual ~EvSwapMap();

	void process();

private:
	CMapProcessor * _mapProcessor;
};

#endif