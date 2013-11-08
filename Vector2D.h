#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class vector2D
{
public:
	vector2D();
	vector2D(float x, float y);
	~vector2D(){}

	float mangitude();

	vector2D operator *=(float);
	vector2D operator *=(vector2D);
	vector2D operator *(vector2D);
	vector2D operator* (float);

	float x;
	float y;
};

#endif