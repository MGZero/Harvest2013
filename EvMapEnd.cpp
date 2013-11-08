#include "EvMapEnd.h"

EvMapEnd::EvMapEnd(CEntity * sender) : CEvent(sender)
{

}

EvMapEnd::~EvMapEnd()
{

}

void EvMapEnd::process()
{
	_sender->_mapEnd();
}