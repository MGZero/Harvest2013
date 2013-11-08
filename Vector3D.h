#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

class vector3D
{
public:
	vector3D();
	vector3D(float x, float y, float z);
	~vector3D(){}

	float mangitude();
	float * returnAsArray();

	vector3D operator *=(float);
	vector3D operator *=(vector3D);
	vector3D operator *(vector3D);
	vector3D operator* (float);
	vector3D operator /=(float);
	vector3D operator /(float);
	vector3D operator /=(vector3D);
	vector3D operator /(vector3D);
	vector3D operator +(vector3D);
	vector3D operator +=(vector3D);
	vector3D operator =(const vector3D&);

	float x;
	float y;
	float z;

private:
	float _dataAsArray[3];
};

#endif