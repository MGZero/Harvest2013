#include "CEntity.h"

CEntity::entityFactory::map_type* CEntity::entityFactory::map = nullptr;
std::pair<std::string, MAPSTORAGE> CEntity::_mapSwapCall = std::make_pair("NULL", disk);
std::vector<std::string> CEntity::_localEvents = std::vector<std::string>();
std::queue<CEntCreation> CEntity::_entCreation = std::queue<CEntCreation>();
std::queue<std::string> CEntity::_entDestruction = std::queue<std::string>();

CEntity::CEntity()
{
	for (int i = 0; i < _localEvents.size(); i++)
	{
		std::string x = _localEvents[i];
		_myEvents.insert(std::make_pair(x, false));
	}
	_destroy = false;
	_enabled = true;
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;

}

void CEntity::attachShaders(const char * vertex, const char * fragment)
{
	/*if (_sprite.isNull())
		return;*/

	_sprite.attachShaders(vertex, fragment);
}

int CEntity::getEntDestructionSize()
{
	return _entDestruction.size();
}

std::string CEntity::getNextEntDestroyer()
{
	std::string out = _entDestruction.back();
	_entDestruction.pop();
	return out;
}

CEntity * CEntity::getNextCollision()
{
	CEntity * out = _collidedWith.back();
	_collidedWith.pop();
	return out;
}

void CEntity::addCollision(CEntity * collider)
{
	_collidedWith.push(collider);
}

void CEntity::initialize(std::string name, int x, int y, int layer, std::string sprite)
{
	this->position.x = x;
	this->position.y = y;
	_layer = layer;
	_mapName = name;

	if (sprite != "")
		_sprite = CContent::createSprite(sprite, vector3D(x,y,0));
}

std::pair<std::string, MAPSTORAGE> CEntity::popMapSwaps()
{
	if (_mapSwapCall.first == "NULL")
		return std::make_pair("NULL", disk);
	else
		return _mapSwapCall;
}

void CEntity::_createEntity(std::string entityType, std::string name, int x, int y, int layer)
{
	CEntCreation ent(entityType, name, x, y, layer);
	_entCreation.push(ent);
}

void CEntity::_swapMap(std::string mapName, MAPSTORAGE location)
{
	_mapSwapCall = std::make_pair(mapName, disk);
}

void CEntity::resetMapSwap()
{
	_mapSwapCall = std::make_pair("NULL", disk);
}

void CEntity::addLocalEvent(std::string eventName)
{
	_localEvents.insert(_localEvents.end(), eventName);
}

int CEntity::getEntCreationSize()
{
	return _entCreation.size();
}

void CEntity::_frame()
{
	_oldPosition = position;

	velocity += (vector3D)acceleration;
	position += (vector3D)velocity;

	momentum = phys::momentum::calcMomentum(velocity, mass);
	force = phys::force::calcForce(acceleration, mass);
	kinetic = phys::energy::calcKineticEnergy(velocity, mass);
}

CEntCreation CEntity::getNextEntCreator()
{
	CEntCreation out = _entCreation.back();
	_entCreation.pop();
	return out;
}