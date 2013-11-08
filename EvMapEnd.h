#ifndef EVMAPEND_H
#define EVMAPEND_H

#include "CEvent.h"
#include "CEntity.h"

class EvMapEnd : public CEvent
{
public:
	EvMapEnd(CEntity * sender);
	virtual ~EvMapEnd();

	void process();
private:


};


#endif