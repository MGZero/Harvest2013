#include "Vector2D.h"

vector2D::vector2D()
{
	x = 0;
	y = 0;
}

vector2D::vector2D(float X, float Y) : x(X), y(Y) {}

float vector2D::mangitude()
{
	float out = 0;

	out = sqrtf( (powf(x,2) + powf(y,2)));
	return out;
}

vector2D vector2D::operator*(float val)
{
	
	float x = this->x;
	float y = this->y;

	x *= val;
	y *= val;
	vector2D out(x,y);
	return out;
}

vector2D vector2D::operator*(vector2D val)
{
	float x = val.x;
	float y = val.y;

	x *= this->x;
	y *= this->y;
	vector2D out(x,y);
	return out;
}

vector2D vector2D::operator*=(float val)
{
	return *(this) * val;
}

vector2D vector2D::operator*=(vector2D val)
{
	return *(this) * val;
}