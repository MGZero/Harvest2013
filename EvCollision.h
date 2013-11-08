#ifndef EVCOLLISION_H
#define EVCOLLISION_H

#include "CEvent.h"
#include "CHitBox.h"

class EvCollision : public CEvent
{
public:
	EvCollision(CEntity * other, CEntity * sender) : CEvent(sender), _other(other){}

	void process();
private:
	CEntity * _other;
};

#endif