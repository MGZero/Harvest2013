#include "Vector4D.h"

vector4D::vector4D()
{
	x = 0;
	y = 0;
	z = 0;
	i = 0;
}

vector4D::vector4D(float X, float Y, float Z, float I) : x(X), y(Y), z(Z), i(I) {}

float vector4D::mangitude()
{
	float out = 0;

	out = sqrtf((powf(x,2) + powf(y,2) + powf(z,2) + powf(i,2)));
	return out;
}

float * vector4D::returnAsArray()
{
	_dataAsArray[0] = x;
	_dataAsArray[1] = y;
	_dataAsArray[2] = z;
	_dataAsArray[3] = i;

	return _dataAsArray;
}

vector4D vector4D::operator*(float val)
{
	
	float x = this->x;
	float y = this->y;
	float z = this->z;
	float i = this->i;

	x *= val;
	y *= val;
	z *= val;
	i *= val;

	vector4D out(x,y,z,i);
	return out;
}

vector4D vector4D::operator*(vector4D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;
	float i = val.i;

	x *= this->x;
	y *= this->y;
	z *= this->z;
	i *= this->i;

	vector4D out(x,y,z,i);
	return out;
}

vector4D vector4D::operator*=(float val)
{
	return *(this) * val;
}

vector4D vector4D::operator*=(vector4D val)
{
	return *(this) * val;
}

vector4D vector4D::operator /=(float val)
{
	return *(this) / val;
}
vector4D vector4D::operator /(float val)
{
	float x = this->x;
	float y = this->y;
	float z = this->z;
	float i = this->i;

	x /= val;
	y /= val;
	z /= val;
	i /= val;

	vector4D out(x,y,z,i);
	return out;
}
vector4D vector4D::operator /=(vector4D val)
{
	return *(this) / val;
}
vector4D vector4D::operator /(vector4D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;

	x /= this->x;
	y /= this->y;
	z /= this->z;
	i /= this->i;

	vector4D out(x,y,z,i);
	return out;
}

vector4D vector4D::operator+(vector4D val)
{
	float x = val.x;
	float y = val.y;
	float z = val.z;
	float i = val.i;

	x += this->x;
	y += this->y;
	z += this->z;
	i += this->i;

	vector4D out(x,y,z,i);
	return out;
}

vector4D vector4D::operator+=(vector4D val)
{
	return *(this) + val;
}

vector4D vector4D::operator=(const vector4D& val)
{
	vector4D out = vector4D(val.x, val.y, val.z, val.i);
	
	return out;
}