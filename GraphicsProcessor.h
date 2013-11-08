#ifndef GRAPHICSPROCESSOR_H
#define GRAPHICSPROCESSOR_H

#include "GLContext.h"
#include "CDrawList.h"
#include "CMap.h"

class CGraphicsProcessor
{
public:
	CGraphicsProcessor(HWND hwnd, int width, int height);
	~CGraphicsProcessor();

	void render(CMap * map);
	static void prepareShader();
	void testDraw();
private:
	

	GLContext * _context;
	CDrawList * _drawList;

	static const char * _basicVertexShader;
	static const char * _basicFragmentShader;
	static unsigned int _vs;
	static unsigned int _fs;
	static unsigned int _shaderProgram;


};


#endif