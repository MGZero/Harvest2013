#include "Vector3D.h"

vector3D::vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

vector3D::vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

float vector3D::mangitude()
{
	float out = 0;

	out = sqrtf((powf(x,2) + powf(y,2) + powf(z,2)));
	return out;
}

float * vector3D::returnAsArray()
{
	_dataAsArray[0] = x;
	_dataAsArray[1] = y;
	_dataAsArray[2] = z;

	return _dataAsArray;
}

vector3D vector3D::operator*(float val)
{
	
	float x = this->x;
	float y = this->y;
	float z = this->z;

	x *= val;
	y *= val;
	z *= val;
	vector3D out(x,y,z);
	return out;
}

vector3D vector3D::operator*(vector3D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;

	x *= this->x;
	y *= this->y;
	z *= this->z;
	vector3D out(x,y,z);
	return out;
}

vector3D vector3D::operator*=(float val)
{
	return *(this) * val;
}

vector3D vector3D::operator*=(vector3D val)
{
	return *(this) * val;
}

vector3D vector3D::operator /=(float val)
{
	return *(this) / val;
}
vector3D vector3D::operator /(float val)
{
	float x = this->x;
	float y = this->y;
	float z = this->z;

	x /= val;
	y /= val;
	z /= val;
	vector3D out(x,y,z);
	return out;
}
vector3D vector3D::operator /=(vector3D val)
{
	return *(this) / val;
}
vector3D vector3D::operator /(vector3D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;

	x /= this->x;
	y /= this->y;
	z /= this->z;
	vector3D out(x,y,z);
	return out;
}

vector3D vector3D::operator+(vector3D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;

	x += this->x;
	y += this->y;
	z += this->z;
	vector3D out(x,y,z);
	return out;
}

vector3D vector3D::operator+=(vector3D val)
{
	return *(this) + val;
}

vector3D vector3D::operator=(const vector3D& val)
{
	vector3D out = vector3D(val.x, val.y, val.z);
	
	return out;
}