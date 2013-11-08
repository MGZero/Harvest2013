#ifndef EVMOUSEPRESS_H
#define EVMOUSEPRESS_H

#include "CEvent.h"
#include "lib\OIS\OISMouse.h"

class EvMousePress : public CEvent
{
public:
	EvMousePress(std::vector<OIS::MouseButtonID> buttonsPressed, CEntity * _sender);
	
	void process();
private:
	std::vector<OIS::MouseButtonID> _buttonsPressed;
};

#endif