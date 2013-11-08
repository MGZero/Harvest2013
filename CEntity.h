#ifndef CENTITY_H_
#define CENTITY_H_

#include <vector>
#include "lib\OIS\OISKeyboard.h"
#include "lib\OIS\OISMouse.h"
#include <list>
#include "AudioProcessor.h"
#include <unordered_map>
#include "CEntCreation.h"
#include "Vector2D.h"
#include "phys.h"
#include "GLContext.h"
#include "CSprite.h"

#include "CContent.h"

class CEntity;
class CEntCreation;
class CHitBox;

enum MAPSTORAGE
{
	disk = 0,
	ram
};

template<typename T> CEntity * createT() { return new T; }

class CEntity
{
public:
	CEntity();
	virtual ~CEntity(){};

	friend class EvKeyPressed;
	friend class EvMapEnd;
	friend class EvDestroy;
	friend class EvCollision;
	friend class EvFrame;
	friend class EvMousePress;

	vector3D position;

	inline std::string name(){return _mapName;}
	
	static std::pair<std::string, MAPSTORAGE> popMapSwaps();
	static void resetMapSwap();
	static void addLocalEvent(std::string eventName);
	static int getEntCreationSize();
	static CEntCreation getNextEntCreator();
	static int getEntDestructionSize();
	static std::string getNextEntDestroyer();
	inline bool getDestructionFlag(){return _destroy;}
	inline void markDestruction(){_destroy = true; _enabled = false;}
	inline bool enabled(){return _enabled;}
	inline std::string type(){return _typeName;}
	inline vector3D getOldPosition(){return _oldPosition;}
	void addCollision(CEntity * collider);
	inline int getCollisionSize(){return _collidedWith.size();}
	CEntity * getNextCollision();
	inline bool isSpriteNull(){return _sprite.isNull();}
	inline CSprite getSprite(){return _sprite;}
	void attachShaders(const char * vertex, const char * fragment);

	virtual void initialize(std::string name, int x, int y, int layer, std::string sprite = "");

	struct entityFactory {
		typedef std::unordered_map<std::string, CEntity*(*)()> map_type;

		static CEntity * createInstance(std::string const& s) {
			map_type::iterator it = getMap()->find(s);
			if(it == getMap()->end())
				return 0;
			return it->second();
		}

		protected:
			static map_type * getMap() {
			if(!map) { map = new map_type; } 
				return map; 
			}

		private:
			static map_type * map;
    };

	template<typename T>
	struct DerivedRegister : entityFactory { 
		DerivedRegister(std::string const& s) { 
			getMap()->insert(std::make_pair(s, &createT<T>));
		}
	};

	phys::velocity velocity;
	phys::acceleration acceleration;
	phys::momentum momentum;
	phys::force force;
	phys::energy kinetic;
	phys::energy potential;
	phys::energy mechanical;
	vector3D scale;
	vector3D angle;
	float mass;

private:
	virtual void _keyDown(std::vector<OIS::KeyCode> keysPressed, CEntity * sender) = 0;
	virtual void _mouseDown(std::vector<OIS::MouseButtonID> buttonsPressed, CEntity * sender) = 0;
	virtual void _mapEnd() = 0;
	virtual void _entDestroy() = 0;
	virtual void _collision(CEntity * other) = 0;
	virtual void _frame(); //we'll use this to do auto updates, such as velocity and acceleration.  If you don't want this functionality, do not call the base method in the child classes

	//system calls
	void _swapMap(std::string mapName, MAPSTORAGE location = disk);
	void _createEntity(std::string entityType, std::string name, int x, int y, int layer);
	void _destroyEntity(std::string name);

	std::string _mapName;
	vector3D _oldPosition;
	int _layer;
	bool _destroy;
	bool _enabled;

	static std::pair<std::string, MAPSTORAGE> _mapSwapCall;
	static std::vector<std::string> _localEvents;
	static std::queue<CEntCreation> _entCreation;
	static std::queue<std::string> _entDestruction;
	std::unordered_map<std::string, bool> _myEvents;

protected:
	std::string _typeName;
	std::queue<CEntity*> _collidedWith;
	CHitBox * _hitBox;
	CSprite _sprite;
};





#endif