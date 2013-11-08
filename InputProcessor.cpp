#include "InputProcessor.h"

bool CInputProcessor::_quitGame = false;

CInputProcessor::CInputProcessor(OIS::ParamList pl)
{
	_inputManager = OIS::InputManager::createInputSystem(pl);
	_keyboard = (OIS::Keyboard*)_inputManager->createInputObject(OIS::OISKeyboard, true);
	_mouse = (OIS::Mouse*)_inputManager->createInputObject(OIS::OISMouse, true);
	

	_keyboard->setEventCallback(this);
	_mouse->setEventCallback(this);
	
}

CInputProcessor::~CInputProcessor()
{
	_inputManager->destroyInputObject(_keyboard);
	OIS::InputManager::destroyInputSystem(_inputManager);
}

void CInputProcessor::processInput()
{
	static int cleanUp = 0;
	_keyReleasedBuffer.clear();
	_keyboard->capture();
	_mouse->capture();

	if (cleanUp++ == 30)
	{
		cleanUp = 0;
		_keyBuffer.shrink_to_fit();
	}
}

bool CInputProcessor::keyPressed(const OIS::KeyEvent & arg)
{
	if (std::find(_keyBuffer.begin(), _keyBuffer.end(), arg.key) == _keyBuffer.end())
	{
		_keyBuffer.push_back(arg.key);
	}

	_quitGame = arg.key == OIS::KC_ESCAPE;
		

	return true;
}

bool CInputProcessor::keyReleased(const OIS::KeyEvent & arg)
{
	_keyBuffer.erase(std::remove(_keyBuffer.begin(), _keyBuffer.end(), arg.key), _keyBuffer.end());
	_keyReleasedBuffer.push_back(arg.key);

	return true;
}

bool CInputProcessor::mouseMoved(const OIS::MouseEvent & arg)
{
	_mouseCoords.x = arg.state.X.rel;
	_mouseCoords.y = arg.state.Y.rel;
	return true;
}

bool CInputProcessor::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	
	if (std::find(_mouseButtonBuffer.begin(), _mouseButtonBuffer.end(), id) == _mouseButtonBuffer.end())
		_mouseButtonBuffer.push_back(id);
		

	return true;
}

bool CInputProcessor::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	_mouseButtonBuffer.erase(std::remove(_mouseButtonBuffer.begin(), _mouseButtonBuffer.end(), id), _mouseButtonBuffer.end());
	_mouseReleasedBuffer.push_back(id);

	return true;
}