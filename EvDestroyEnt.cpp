#include "EvDestroyEnt.h"

void EvDestroyEnt::process()
{
	if (_killThis)
		delete _killThis;

	_killThis = nullptr;
}