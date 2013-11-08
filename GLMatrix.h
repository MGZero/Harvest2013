#ifndef GLMATRIX_H
#define GLMATRIX_H

#include "Vector4D.h"

//this is a 4x4 matrix intended to be used by openGL Transformations

class GLMatrix
{
public:
	GLMatrix(bool identity);
	GLMatrix(){}
	GLMatrix(float * values);

	float matrix[16];

	GLMatrix operator * (vector4D);
	void operator *= (vector4D);
	GLMatrix operator * (GLMatrix);

	
};

#endif GLMATRIX_H