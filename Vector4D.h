#ifndef VECTOR4D_H
#define VECTOR4D_H

#include <math.h>

class vector4D
{
public:
	vector4D();
	vector4D(float x, float y, float z, float i);
	~vector4D(){}

	float mangitude();
	float * returnAsArray();

	vector4D operator *=(float);
	vector4D operator *=(vector4D);
	vector4D operator *(vector4D);
	vector4D operator* (float);
	vector4D operator /=(float);
	vector4D operator /(float);
	vector4D operator /=(vector4D);
	vector4D operator /(vector4D);
	vector4D operator +(vector4D);
	vector4D operator +=(vector4D);
	vector4D operator =(const vector4D&);

	float x;
	float y;
	float z;
	float i;

private:
	float _dataAsArray[4];
};

#endif