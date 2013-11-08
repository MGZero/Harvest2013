#ifndef _KEYPRESSED_H_
#define _KEYPRESSED_H_

#include "CEvent.h"
#include "lib/OIS/OISKeyboard.h"

class EvKeyPressed : public CEvent
{
public:
	EvKeyPressed(std::vector<OIS::KeyCode> keysPressed, CEntity * sender);
	virtual ~EvKeyPressed();

	void process();

private:
	std::vector<OIS::KeyCode> _keysPressed;
};

#endif

