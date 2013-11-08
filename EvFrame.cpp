#include "EvFrame.h"

void EvFrame::process()
{
	if (_sender)
		_sender->_frame();
}