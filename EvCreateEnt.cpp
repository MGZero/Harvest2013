#include "EvCreateEnt.h"

EvCreateEnt::EvCreateEnt(CEntCreation entCreation, CMapProcessor * mapProcessor) : CEvent()
{
	_mapProcessor = mapProcessor;
	_entCreation = entCreation;
}

void EvCreateEnt::process()
{
	CEntity * ent = nullptr;
	int layer = 0;

	ent = CEntity::entityFactory::createInstance(_entCreation.getType());
	ent->initialize(_entCreation.getName(), _entCreation.x(), _entCreation.y(), _entCreation.layer());
	_mapProcessor->insertEntity(ent, layer);


}