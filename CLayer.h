#ifndef CLAYER_H
#define CLAYER_H

#include "CPlayer.h"
#include "CHitBox.h"
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include <vector>

typedef std::unordered_map<std::string, CEntity*> entityListing;

class CLayer
{
public:
	CLayer(std::vector<CEntity*> entities);
	CLayer(){};
	virtual ~CLayer();

	CEntity & getEntity(std::string name);
	inline int getEntCount(){return _entities.size();}

	friend class CMap;
	friend class CGraphicsProcessor;
private:
	std::unordered_map<std::string, CEntity*> _entities;
	std::vector<CHitBox*> _hitBoxes;

	void _drawLayer();
	void _checkCollisions();
};

#endif