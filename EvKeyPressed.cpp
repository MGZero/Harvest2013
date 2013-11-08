#include "EvKeyPressed.h"

EvKeyPressed::EvKeyPressed(std::vector<OIS::KeyCode> keysPressed, CEntity * _sender) : CEvent(_sender)
{
	_keysPressed = keysPressed;
}

EvKeyPressed::~EvKeyPressed(){}

void EvKeyPressed::process()
{
	_sender->_keyDown(_keysPressed, _sender);
}