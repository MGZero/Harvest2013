#include "CEventQueue.h"

CEvent * CEventQueue::popEvent()
{
	if (this->empty())
		return nullptr;

	CEvent * outPut = this->front();
	this->pop();
	return outPut;
}