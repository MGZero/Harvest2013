#ifndef _INPUTPROCESSOR_H_
#define _INPUTPROCESSOR_H_

#include "lib/OIS/OISKeyboard.h"
#include "lib/OIS/OISMouse.h"
#include "lib/OIS/OISJoystick.h"
#include "lib/OIS/OISInputManager.h"
#include "Vector2D.h"
#include <vector>
#include <algorithm>


class CInputProcessor : public OIS::KeyListener, public OIS::MouseListener
{
public:
	CInputProcessor(OIS::ParamList pl);
	virtual ~CInputProcessor();
	
	friend class CEventProcessor;

	void processInput();
	inline vector2D mouseCoords(){return _mouseCoords;}
	inline bool quitGame(){return _quitGame;}

private:
	OIS::InputManager * _inputManager;
	OIS::Keyboard * _keyboard;
	OIS::Mouse * _mouse;
	std::vector<OIS::KeyCode> _keyBuffer;
	std::vector<OIS::KeyCode> _keyReleasedBuffer;
	std::vector<OIS::MouseButtonID> _mouseButtonBuffer;
	std::vector<OIS::MouseButtonID> _mouseReleasedBuffer;

	vector2D _mouseCoords;
	static bool _quitGame;


	bool keyPressed(const OIS::KeyEvent & arg);
	bool keyReleased(const OIS::KeyEvent & arg);
	bool mouseMoved( const OIS::MouseEvent &arg );
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
};

#endif