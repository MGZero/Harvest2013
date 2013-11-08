#include "GLMatrix.h"

GLMatrix::GLMatrix(bool identity)
{
	matrix[0] = (float)identity;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = (float)identity;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = (float)identity;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = (float)identity;
}

GLMatrix::GLMatrix(float * values)
{
	matrix[0] = values[0];
	matrix[1] = values[1];
	matrix[2] = values[2];
	matrix[3] = values[3];

	matrix[4] = values[4];
	matrix[5] = values[5];
	matrix[6] = values[6];
	matrix[7] = values[7];

	matrix[8] = values[8];
	matrix[9] = values[9];
	matrix[10] = values[10];
	matrix[11] = values[11];

	matrix[12] = values[12];
	matrix[13] = values[13];
	matrix[14] = values[14];
	matrix[15] = values[15];
}

GLMatrix GLMatrix::operator*(vector4D value)
{
	GLMatrix out = *this;

	//multiply every 4 elements by an element of the vector
	out.matrix[0] *= value.x;
	out.matrix[1] *= value.x;
	out.matrix[2] *= value.x;
	out.matrix[3] *= value.x;

	out.matrix[4] *= value.y;
	out.matrix[5] *= value.y;
	out.matrix[6] *= value.y;
	out.matrix[7] *= value.y;

	out.matrix[8] *= value.z;
	out.matrix[9] *= value.z;
	out.matrix[10] *= value.z;
	out.matrix[11] *= value.z;

	out.matrix[12] *= value.i;
	out.matrix[13] *= value.i;
	out.matrix[14] *= value.i;
	out.matrix[15] *= value.i;

	return out;
}

GLMatrix GLMatrix::operator*(GLMatrix value)
{
	GLMatrix out;
	float val = 0;


	//First column
	val = (matrix[0] * value.matrix[0] + matrix[1] * value.matrix[4] + matrix[2] * value.matrix[8] + matrix[3] * value.matrix[12]);
	out.matrix[0] = val;

	val = (matrix[4] * value.matrix[0] + matrix[5] * value.matrix[4] + matrix[6] * value.matrix[8] + matrix[7] * value.matrix[12]);
	out.matrix[4] = val;

	val = (matrix[8] * value.matrix[0] + matrix[9] * value.matrix[4] + matrix[10] * value.matrix[8] + matrix[11] * value.matrix[12]);
	out.matrix[8] = val;

	val = (matrix[12] * value.matrix[0] + matrix[13] * value.matrix[4] + matrix[14] * value.matrix[8] + matrix[15] * value.matrix[12]);
	out.matrix[12] = val;

	//second column
	val = (matrix[0] * value.matrix[1] + matrix[1] * value.matrix[5] + matrix[2] * value.matrix[9] + matrix[3] * value.matrix[13]);
	out.matrix[1] = val;

	val = (matrix[4] * value.matrix[1] + matrix[5] * value.matrix[5] + matrix[6] * value.matrix[9] + matrix[7] * value.matrix[13]);
	out.matrix[5] = val;

	val = (matrix[8] * value.matrix[1] + matrix[9] * value.matrix[5] + matrix[10] * value.matrix[9] + matrix[11] * value.matrix[13]);
	out.matrix[9] = val;

	val = (matrix[12] * value.matrix[1] + matrix[13] * value.matrix[5] + matrix[14] * value.matrix[9] + matrix[15] * value.matrix[13]);
	out.matrix[13] = val;

	//Third Column
	val = (matrix[0] * value.matrix[2] + matrix[1] * value.matrix[6] + matrix[2] * value.matrix[10] + matrix[3] * value.matrix[14]);
	out.matrix[2] = val;

	val = (matrix[4] * value.matrix[2] + matrix[5] * value.matrix[6] + matrix[6] * value.matrix[10] + matrix[7] * value.matrix[14]);
	out.matrix[6] = val;

	val = (matrix[8] * value.matrix[2] + matrix[9] * value.matrix[6] + matrix[10] * value.matrix[10] + matrix[11] * value.matrix[14]);
	out.matrix[10] = val;

	val = (matrix[12] * value.matrix[2] + matrix[13] * value.matrix[6] + matrix[14] * value.matrix[10] + matrix[15] * value.matrix[14]);
	out.matrix[14] = val;

	//Fourth Column
	val = (matrix[0] * value.matrix[3] + matrix[1] * value.matrix[7] + matrix[2] * value.matrix[11] + matrix[3] * value.matrix[15]);
	out.matrix[3] = val;

	val = (matrix[4] * value.matrix[3] + matrix[5] * value.matrix[7] + matrix[6] * value.matrix[11] + matrix[7] * value.matrix[15]);
	out.matrix[7] = val;

	val = (matrix[8] * value.matrix[3] + matrix[9] * value.matrix[7] + matrix[10] * value.matrix[11] + matrix[11] * value.matrix[15]);
	out.matrix[11] = val;

	val = (matrix[12] * value.matrix[3] + matrix[13] * value.matrix[7] + matrix[14] * value.matrix[11] + matrix[15] * value.matrix[15]);
	out.matrix[15] = val;



	return out;
}

void GLMatrix::operator*=(vector4D value)
{
	*this = *(this) * value;
}