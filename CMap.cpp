#include "CMap.h"

CMap::~CMap()
{
	for (std::map<int, CLayer*>::iterator itr = _layers.begin(); itr != _layers.end(); itr++)
	{
		delete itr->second;
		itr->second = nullptr;
	}

	_layers.clear();
	_entityRegistry.clear();
}

CMap::CMap(bool test)
{
	_layerCount = 1;
	_layers.insert(std::make_pair(0, new CLayer()));
}

CMap CMap::createMap(std::string mapFile)
{
	CMap out;
	std::ifstream map(mapFile.c_str(), std::ios::binary | std::ios::in);

	char buffer[] = {'0','0','0','0'};
	int intBuffer = 0;

	//read map name
	map.read((char*)&intBuffer, 1);
	map.read((char*)&out._mapName, intBuffer);

	//num layers
	map.read((char*)&out._layerCount, 1);

	for (int i = 0; i < out._layerCount; i++)
	{
		CLayer * layer = new CLayer();

		//read entity count
		map.read((char*)&intBuffer, 1);
		for (int j = 0; j < intBuffer; j++)
		{
			std::string type = "";
			std::string name = "";
			std::string sprite = "";
			std::string vertexShader = "";
			std::string fragmentShader = "";
			int x = 0, y = 0, layer = 0;
			int strLen = 0;

			//ent type
			map.read((char*)&strLen,1);
			map.read((char*)&type, strLen);

			//ent name
			map.read((char*)&strLen,1);
			map.read((char*)&name, strLen);

			//x and y
			map.read((char*)&x,1);
			map.read((char*)&y,1);

			map.read((char*)&strLen,1);
			map.read((char*)&sprite, strLen);

			map.read((char*)&strLen,1);
			map.read((char*)&vertexShader, strLen);

			map.read((char*)&strLen,1);
			map.read((char*)&fragmentShader, strLen);

			if (sprite == "__NULLSPRITE")
				sprite = "";

			CEntity * ent = CEntity::entityFactory::createInstance(type);
			ent->initialize(name, x, y, i, sprite);
			ent->attachShaders(CContent::getShader(vertexShader), CContent::getShader(fragmentShader));

			out.insertEntity(ent, layer);
			
		}

		//read hitbox count
		map.read((char*)&intBuffer, 1);
		for (int j = 0; j < intBuffer; j++)
		{
			vector2D coordinates;
			vector2D dimensions;
			std::string entName;
			int strLen;
			bool isSolid;
			CHitBox* hitBox = nullptr;
			CEntity * ent = nullptr;

			map.read((char*)&coordinates.x,1);
			map.read((char*)&coordinates.y,1);

			map.read((char*)&dimensions.x,1);
			map.read((char*)&dimensions.y,1);

			map.read((char*)&strLen,1);
			map.read((char*)&entName, strLen);

			if (entName != "__NOENT")
			{
				for (std::unordered_map<std::string, CEntity*>::iterator itr = out._entityRegistry.begin(); itr != out._entityRegistry.end(); itr++)
				{
					if (itr->second->name() == entName)
					{
						ent = itr->second;
						break;
					}
				}
			}
			hitBox = new CHitBox(ent, coordinates.x, coordinates.y, dimensions.x, dimensions.y, isSolid);
			out.insertHitBox(hitBox, layer);
		}

		out._layers.insert(std::make_pair(i, layer));

	}

	map.close();

	return out;
}

void CMap::insertEntity(CEntity *entity, int layer)
{
	_layers[layer]->_entities.insert(std::make_pair(entity->name(), entity));
	_entityRegistry.insert(std::make_pair(entity->name(), entity));
}

void CMap::insertEntity(CEntity * entity, CLayer * layer)
{
	layer->_entities.insert(std::make_pair(entity->name(), entity));
	_entityRegistry.insert(std::make_pair(entity->name(), entity));
}

void CMap::insertHitBox(CHitBox * hitBox, int layer)
{
	_layers[layer]->_hitBoxes.push_back(hitBox);
	_hitBoxRegistry.push_back(hitBox);
}

void CMap::insertHitBox(CHitBox * hitBox, CLayer * layer)
{
	layer->_hitBoxes.push_back(hitBox);
	_hitBoxRegistry.push_back(hitBox);
}

CEntity * CMap::searchRegistry(std::string entityName)
{
	std::unordered_map<std::string, CEntity*>::iterator itr = _entityRegistry.find(entityName);

	if (itr == _entityRegistry.end())
		return nullptr;
	
	return itr->second; 
}

void CMap::checkCollisions()
{
	if (_layers.size() > 0)
		for (std::map<int, CLayer*>::iterator itr = _layers.begin(); itr != _layers.end(); itr++)
			itr->second->_checkCollisions();
}