#include "EvCollision.h"

void EvCollision::process()
{
	if (_sender)
	{
		_sender->_collision(_other);
		if (_sender->_hitBox->isSolid())
			_sender->_hitBox->solidCollide(_other->_hitBox);
	}
	
}