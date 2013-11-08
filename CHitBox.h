#ifndef CHITBOX_H
#define CHITBOX_H

#include "CEntity.h"
#include "Vector2D.h"
#include "Vector3D.h"

class CHitBox
{
public:
	CHitBox(CEntity * entity, float offsetx, float offsety, float width, float height, bool isSolid = false);
	~CHitBox();
	bool checkCollision(CEntity * sender);
	bool checkCollision(vector3D point);

	inline float halfWidth(){return _halfSize.x;}
	inline float halfHeight(){return _halfSize.y;}
	inline vector3D center(){return _center;}
	inline vector3D size(){ return _halfSize * 2.0f;}
	inline vector3D offSet(){ return vector3D(_center.x - _halfSize.x, _center.y - _halfSize.y, 0);}
	std::string getEntType();
	void addCollision(CEntity * collider);
	inline bool isSolid(){return _isSolid;}


	void setSize(vector3D val);
	void setOffSet(vector3D val);
	bool checkCollision(CHitBox & otherBox);
	void solidCollide(CHitBox * other);

	CEntity * entity;

private:

	

	vector3D _halfSize;
	vector3D _center;
	
	bool _isSolid;

};

#endif