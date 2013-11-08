#ifndef _CEVENTQUEUE_H_
#define _CEVENTQUEUE_H_

#include <queue>
#include "CEvent.h"

class CEventQueue : public std::queue<CEvent*>
{
public:
	CEvent * popEvent();
};

#endif