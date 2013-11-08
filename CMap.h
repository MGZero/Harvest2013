#ifndef CMAP_H
#define CMAP_H

#include "CLayer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Vector2D.h"

#define MAXLAYERS 16



class CMap
{
public:
	CMap(){};
	CMap(bool);
	virtual ~CMap();

	friend class CMapProcessor;
	friend class CGraphicsProcessor;

	static CMap createMap(std::string mapFile);
	void insertEntity(CEntity * ent, int layer);
	void insertEntity(CEntity * ent, CLayer * layer);
	void insertHitBox(CHitBox * hitBox, int layer);
	void insertHitBox(CHitBox * hotBox, CLayer * layer);
	void checkCollisions();
	CEntity * searchRegistry(std::string entityName);


private:
	std::map<int,CLayer*> _layers;
	std::string _mapName;
	int _layerCount;
	std::unordered_map<std::string, CEntity*> _entityRegistry;
	std::vector<CHitBox*> _hitBoxRegistry;

	void _drawLayer();

};

#endif