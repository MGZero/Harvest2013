#ifndef EVDESTROYENT_H
#define EVDESTROYENT_H

#include "CEvent.h"

class EvDestroyEnt : public CEvent
{
public:
	EvDestroyEnt(CEntity * sender) : _killThis(sender){}
	~EvDestroyEnt(){}

	void process();

private:
	CEntity * _killThis;
};

#endif