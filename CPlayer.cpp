#include "CPlayer.h"

CEntity::DerivedRegister<CBasePlayer> CBasePlayer::_builder("CPlayer");

CBasePlayer::CBasePlayer()
{
	_typeName = "CPlayer";
	_sprite = CContent::createSprite("test", vector3D(0,0,0));
	
	
}

void CBasePlayer::initialize(std::string name, int x, int y, int layer, std::string sprite)
{
	CEntity::initialize(name, x, y, layer, sprite);

	//if (!_sprite.isNull())
	//{
		//float vectors[] = {0,0,0,0,0,0,0,0,0,0,0,0};
		float vectors[] = {
			0.0f,  0.5f,  0.0f,
			0.0f, -0.5f,  0.0f,
			0.5f, -0.5f,  0.0f,
			0.5f, -0.5f,  0.0f,
			0.5f,  0.5f,  0.0f,
			0.0f,  0.5f,  0.0f
		};

		_sprite.prepareVertices(vectors);
		_sprite.prepareTexture();
		_sprite.prepareVAO();

	//}

}

void CBasePlayer::_keyDown(std::vector<OIS::KeyCode> keysPressed, CEntity * sender)
{
	

	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_LEFT) != keysPressed.end()))
		velocity.x = -.001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_RIGHT) != keysPressed.end()))
		velocity.x = .001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_UP) != keysPressed.end()))
		velocity.y = .001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_DOWN) != keysPressed.end()))
		velocity.y = -.001f;

	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_0) != keysPressed.end()))
		scale.x += .001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_9) != keysPressed.end()))
		scale.x -= .001f;

	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_1) != keysPressed.end()))
		angle.y += .001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_2) != keysPressed.end()))
		angle.x += .001f;
	if ((std::find(keysPressed.begin(), keysPressed.end(), OIS::KC_3) != keysPressed.end()))
		angle.z += .001f;

	
	_sprite.rotate(angle);
	_sprite.scale(scale);

	_sprite.updateTransformation();

	
	
}

void CBasePlayer::_frame()
{
	position.x += velocity.x;
	position.y += velocity.y;
	_sprite.translate(position);

	velocity.x = 0;
	velocity.y = 0;
}

