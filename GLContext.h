#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <sstream>

#include "CDrawList.h"


class GLContext
{
public:
	GLContext(void);
	GLContext(HWND hwnd);
	~GLContext(void);

	bool create30Context(HWND hwnd);
	void setupScene(void);
	void resize(int w, int h);
	void renderScene(CDrawList *);
	void renderScene(unsigned int shader);

	//test
	unsigned int vbo;
	unsigned int vao;

	static const char * basicVertexShader;
	static const char * basicFragmentShader;
	static const char * texturedFragmentShader;
	static const char * texturedVertexShader;

private:
	int _winWidth;
	int _winHeight;

	float * points;

protected:
	HGLRC _hrc;
	HDC _hdc;
	HWND _hwnd;
};

#endif