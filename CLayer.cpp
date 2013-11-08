#include "CLayer.h"

CLayer::CLayer(std::vector<CEntity*> entities)
{
	for (std::vector<CEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++)
		_entities.insert(std::make_pair((*itr)->name(), *itr));
}

CLayer::~CLayer()
{
	for (entityListing::iterator itr = _entities.begin(); itr != _entities.end(); itr++)
	{
		if (itr->second != nullptr)
		{
			delete (itr->second);
			itr->second = nullptr;
		}
	}
	_entities.clear();

	for (std::vector<CHitBox*>::iterator itr = _hitBoxes.begin(); itr != _hitBoxes.end(); itr++)
	{
		if ((*itr) != nullptr)
		{
			delete (*itr);
			(*itr) = nullptr;
		}
	}
	_hitBoxes.clear();
}

CEntity & CLayer::getEntity(std::string name)
{
	return *(_entities[name]);
}

void CLayer::_checkCollisions()
{
	for (std::vector<CHitBox*>::iterator outter = _hitBoxes.begin(); outter != _hitBoxes.end(); outter++)
		for (std::vector<CHitBox*>::iterator inner = outter + 1; inner != _hitBoxes.end(); inner++)
			if ((*outter)->checkCollision(*(*inner)))
				(*outter)->addCollision((*inner)->entity);
}