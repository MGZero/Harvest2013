#include "CHitBox.h"

CHitBox::~CHitBox()
{
	entity = nullptr;
}

CHitBox::CHitBox(CEntity * entity, float offsetx, float offsety, float width, float height, bool isSolid)
{
	this->entity = entity;
	_isSolid = isSolid;

	_halfSize = vector3D(width * .5f, height * .5f, 0);
    _center = vector3D(offsetx+_halfSize.x, offsety+_halfSize.y, 0); 
}

void CHitBox::setSize(vector3D val)
{
	_center.x = (_center.x - _halfSize.x) + val.x;
    _center.y = (_center.y - _halfSize.y) + val.y;
    _halfSize = val * .5f;
}

void CHitBox::setOffSet(vector3D val)
{
	_center.x = _halfSize.x + val.x;
    _center.y = _halfSize.y + val.y;
}

void CHitBox::solidCollide(CHitBox * other)
{
	 //Calculate How much to move to get out of collision moving towards last collisionless point
			CHitBox * otherbox = other;
			

			if (otherbox->entity != nullptr && entity != nullptr)
			{
				//Calculate how far in we went
				float distx = (other->entity->position.x + otherbox->center().x) - (entity->position.x + _center.x);
				//distx = (float)Math.Sqrt(distx * distx);
				float disty = (other->entity->position.y + otherbox->center().y) - (entity->position.y + _center.y);
				//disty = (float)Math.Sqrt(disty * disty);
			
				float lenx = halfWidth() + other->halfWidth();
				float leny = halfHeight() + other->halfHeight();
			
				int px = 1;
				int py = 1;
			
				if (otherbox->entity->position.x + otherbox->center().x < entity->position.x + _center.x)
					px = -1;
				if (otherbox->entity->position.y + otherbox->center().y < entity->position.y + _center.y)
					py = -1;
			
				float penx = px*(distx - lenx);
				float peny = py*(disty - leny);
				//Resolve closest to previous position
				float diffx = (entity->position.x + penx) - entity->getOldPosition().x;
				diffx *= diffx;
				float diffy = (entity->position.y + peny) - entity->getOldPosition().y;
				diffy *= diffy;

				if (diffx < diffy)
					entity->position.x += penx; //TODO: dont make a new vector every time
				else if (diffx > diffy)
					entity->position.y += peny; //Same here 
				else
					entity->position = vector3D(entity->position.x + penx, entity->position.y + peny, 0); //Corner cases 
			}
			
}

void CHitBox::addCollision(CEntity * collider)
{
	if (entity)
		entity->addCollision(collider);
}

std::string CHitBox::getEntType()
{
	if (entity)
		return entity->type();

	return "__NOENT";
}

bool CHitBox::checkCollision(CHitBox &otherBox)
{
	float distance = 0;
    float length = 0;

	distance = abs((entity->position.x + _center.x) - (otherBox.entity->position.x + otherBox._center.x));
    length = _halfSize.x + otherBox._halfSize.x;

    if (distance < length)
    {

		distance = abs((entity->position.y + _center.y) - (otherBox.entity->position.y + otherBox._center.y));
        length = _halfSize.y + otherBox._halfSize.y;

        return distance < length;
    }
    return false;
}