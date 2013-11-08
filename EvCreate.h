#ifndef EVCREATE_H
#define EVCREATE_H

#include "CEvent.h"

class EvCreate : public CEvent
{
public:
	EvCreate(CEntity * sender);
	virtual ~EvCreate(){};

	void process();


};

#endif