#ifndef CPLAYER_H
#define CPLAYER_H

#include "CEntity.h"

class CBasePlayer : public CEntity
{
public:
	CBasePlayer();
	~CBasePlayer(){}

	void initialize(std::string name, int x, int y, int layer, std::string sprite = "");

private:

	static CEntity::DerivedRegister<CBasePlayer> _builder;

	void _mapEnd(){}
	void _keyDown(std::vector<OIS::KeyCode> keysPressed, CEntity * sender);
	void _entDestroy(){}
	void _collision(CEntity * other){}
	void _frame();
	void _mouseDown(std::vector<OIS::MouseButtonID> buttonsPressed, CEntity * sender){}
};

#endif