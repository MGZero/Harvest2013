#ifndef EVFRAME_H
#define EVFRAME_H

#include "CEvent.h"

class EvFrame : public CEvent
{
public:
	EvFrame(CEntity * sender) : CEvent(sender){}

	void process();
private:


};

#endif