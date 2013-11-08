#ifndef EVDESTROY_H
#define EVDESTROY_H

#include "CEvent.h"

class EvDestroy : public CEvent
{
public:
	EvDestroy(CEntity * sender);
	virtual ~EvDestroy(){}

	void process();
};

#endif