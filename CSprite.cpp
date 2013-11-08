#include "CSprite.h"

CSprite::CSprite(FIBITMAP * dib, vector3D coordinates) : _shader(-1), _vao(0), _vbo(0)
{
	_isNull = true;
	_transformationMatrix = GLMatrix(true);
	_rotationMatrix = GLMatrix(true);
	_scaleMatrix = GLMatrix(true);
	_translationMatrix = GLMatrix(true);
	_rotationX = GLMatrix(true);
	_rotationY = GLMatrix(true);
	_rotationZ = GLMatrix(true);

	/*glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), coordinates.returnAsArray(), GL_STATIC_DRAW);*/

	

	if (dib != nullptr)
	{
		_bits = FreeImage_GetBits(dib);
		_width = FreeImage_GetWidth(dib);
		_height = FreeImage_GetHeight(dib);



		glGenTextures(1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, _bits);
		_isNull = false;

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, _texID);

		////texture coordinates
		//float texcoords[] = {
		//	0.0f, 1.0f,
		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f
		//};
		//

		//glGenBuffers(1, &_texVbo);
		//glBindBuffer(GL_ARRAY_BUFFER, _texVbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

	}
	//prepare vertex attributes
	/*glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);*/

	/*if (dib != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _texVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);
	}*/
	
}

void CSprite::prepareTexture()
{
	float texcoords[] = {
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};
		

		glGenBuffers(1, &_texVbo);
		glBindBuffer(GL_ARRAY_BUFFER, _texVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, _texVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);


}

CSprite::CSprite(std::string fileName, vector3D coordinates) : _shader(-1), _vao(0), _vbo(0)
{
	_isNull = true;
	_transformationMatrix = GLMatrix(true);
	if (fileName != "__NOSPRITE")
	{
		std::ifstream input(fileName.c_str(), std::ios::in);
		FreeImageIO io;

		//load the image data
		io.read_proc  = _readProc;
		io.write_proc = _writeProc;
		io.seek_proc  = _seekProc;
		io.tell_proc  = _tellProc;

		FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)input, 0);

		if (format != FIF_PNG)
			return;

		FIBITMAP * dib = FreeImage_LoadFromHandle(format, &io, (fi_handle)input, 0);
		_bits = FreeImage_GetBits(dib);
		_width = FreeImage_GetWidth(dib);
		_height = FreeImage_GetHeight(dib);

		glGenTextures(1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _bits);

		FreeImage_Unload(dib);
		dib = 0;
		input.close();
		_isNull = false;
	}
}

void CSprite::updateTransformation()
{
	_transformationMatrix = _scaleMatrix * _rotationMatrix *_translationMatrix;
}

void CSprite::translate(vector3D direction)
{


	_translationMatrix.matrix[12] = direction.x;
	_translationMatrix.matrix[13] = direction.y;
	_translationMatrix.matrix[14] = direction.z;
}

void CSprite::scale(vector3D multiplier)
{
	

	_scaleMatrix.matrix[0] = multiplier.x;
	_scaleMatrix.matrix[5] = multiplier.y;
	_scaleMatrix.matrix[10] = multiplier.z;
}

void CSprite::rotate(vector3D angle)
{
	//x
	_rotationX.matrix[5] = cos(angle.x);
	_rotationX.matrix[6] = -sin(angle.x);
	_rotationX.matrix[9] = sin(angle.x);
	_rotationX.matrix[10] = cos(angle.x);

	//y
	_rotationY.matrix[0] = cos(angle.y);
	_rotationY.matrix[2] = sin(angle.y);
	_rotationY.matrix[8] = -sin(angle.y);
	_rotationY.matrix[10] = cos(angle.y);

	//z
	_rotationZ.matrix[0] = cos(angle.z);
	_rotationZ.matrix[1] = -sin(angle.z);
	_rotationZ.matrix[4] = sin(angle.z);
	_rotationZ.matrix[5] = cos(angle.z);

	_rotationMatrix = _rotationX * _rotationY * _rotationZ;
}

void CSprite::prepareVAO()
{
	//prepare vertex attributes
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);
	glBindBuffer(GL_ARRAY_BUFFER, _texVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);
}

void CSprite::prepareVertices(float vertices[18])
{

	//prepare the vertex buffers
	int x = 0;
	glGenBuffers(1, &_vbo);
	x = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	x = glGetError();
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);
	x = glGetError();
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);

	
}

void CSprite::attachShaders(const char * vertexShader, const char * fragmentShader)
{
	//error handling
	//TODO: Check this with regex
	if (fragmentShader == "")
		return;

	if (vertexShader == "")
		return;

	

	int x = 0;
	//basic vertex shader
	unsigned int _vs = glCreateShader(GL_VERTEX_SHADER);
	x = glGetError();
	glShaderSource(_vs, 1, &vertexShader, 0);
	x = glGetError();
	glCompileShader(_vs);
	x = glGetError();
	

	//basic fragment shader
	unsigned int _fs = glCreateShader(GL_FRAGMENT_SHADER);
	x = glGetError();
	glShaderSource(_fs, 1, &fragmentShader, 0);
	x = glGetError();
	glCompileShader(_fs);

	x = glGetError();

	//create and link shader program
	_shader = glCreateProgram();
	x = glGetError();
	glAttachShader(_shader, _vs);
	x = glGetError();
	glAttachShader(_shader, _fs);
	x = glGetError();
	glLinkProgram(_shader);

	x = glGetError();

	//get the location of the matrix within
	_matrixLocation = glGetUniformLocation(_shader, "matrix");
	
	x = glGetError();

}