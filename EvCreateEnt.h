#ifndef EVCREATEENT_H
#define EVCREATEENT_H

#include "CEvent.h"
#include "MapProcessor.h"
#include "CEntCreation.h"
//#include "ent

class EvCreateEnt : public CEvent
{
public:
	EvCreateEnt(CEntCreation entCreation, CMapProcessor * mapProcessor);
	~EvCreateEnt(){};

	void process();

private:
	CMapProcessor * _mapProcessor;
	CEntCreation _entCreation;
};

#endif