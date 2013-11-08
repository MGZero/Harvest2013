#ifndef CSPRITE_H
#define CSPRITE_H

#include "GLMatrix.h"
#include <gl\glew.h>
#include <gl\wglew.h>
#include <gl\GL.h>
#include <string>
#include <fstream>
#include <iostream>
#include "shaders.h"

#include "FreeImage.h"
#include "Vector3D.h"
#include "Vector4D.h"

class CSprite
{
public:
	CSprite(std::string fileName, vector3D coordinates);
	CSprite(FIBITMAP * dib, vector3D coordinates);
	CSprite(){_isNull = true; _transformationMatrix = GLMatrix(true);}
	~CSprite(){}

	void attachShaders(const char * vertexShader, const char * fragmentShader);
	void prepareVertices(float verticies[18]);
	void prepareVAO();
	void prepareTexture();

	inline bool isNull(){return _isNull;}
	inline unsigned int getShader(){return _shader;}
	inline unsigned int getVBO(){return _vbo;}
	inline unsigned int getVAO(){return _vao;}
	inline unsigned int getWidth(){return _width;}
	inline unsigned int getHeight(){return _height;}
	inline unsigned int getMatrixLocation(){return _matrixLocation;}
	inline GLuint getTexID(){return _texID;}
	inline GLMatrix getMatrix(){return _transformationMatrix;}
	inline unsigned int getTexVbo(){return _texVbo;}

	//transformations
	void translate(vector3D direction);
	void scale(vector3D multiplier);
	void rotate(vector3D angle);
	void updateTransformation();

private:
	GLMatrix _transformationMatrix;
	GLMatrix _rotationMatrix;

	GLMatrix _rotationX;
	GLMatrix _rotationY;
	GLMatrix _rotationZ;

	GLMatrix _scaleMatrix;
	GLMatrix _translationMatrix;
	unsigned int _vbo; //vertex buffer object
	unsigned int _vao; //vertex attribute object
	unsigned int _shader; //shader program. -1 means use basic shaders.
	unsigned int _texVbo;
	unsigned int _matrixLocation;
	GLuint _texID;
	BYTE * _bits;
	unsigned int _width;
	unsigned int _height;
	bool _isNull;

	static unsigned DLL_CALLCONV
	_readProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
		return fread(buffer, size, count, (FILE *)handle);
	}

	static unsigned DLL_CALLCONV
	_writeProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
		return fwrite(buffer, size, count, (FILE *)handle);
	}

	static int DLL_CALLCONV
	_seekProc(fi_handle handle, long offset, int origin) {
		return fseek((FILE *)handle, offset, origin);
	}

	static long DLL_CALLCONV
	_tellProc(fi_handle handle) {
		return ftell((FILE *)handle);
	}

};


#endif