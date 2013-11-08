#include "EvMousePress.h"

EvMousePress::EvMousePress(std::vector<OIS::MouseButtonID> buttonsPressed, CEntity * _sender) : _buttonsPressed(buttonsPressed), CEvent(_sender)
{

}

void EvMousePress::process()
{
	if (_sender)
		_sender->_mouseDown(_buttonsPressed, _sender);
}