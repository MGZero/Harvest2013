#include "EvDestroy.h"

EvDestroy::EvDestroy(CEntity * sender) : CEvent(sender)
{

}

void EvDestroy::process()
{
	_sender->_entDestroy();
}