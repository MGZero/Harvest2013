#include "GLContext.h"

const char * GLContext::basicVertexShader =
	"#version 400\n"
	"in vec3 vp;"
	"uniform mat4 matrix;"
	"void main () {"
	"  gl_Position = matrix * vec4 (vp, 1.0);"
	"}";

const char * GLContext::basicFragmentShader =
	"#version 400\n"
	"out vec4 frag_color;"
	"void main () {"
	"  frag_color = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";

const char * GLContext::texturedFragmentShader = 
	"#version 400\n"
	"in vec2 texture_coordinates;"
	"uniform sampler2D basic_texture;"
	"out vec4 frag_color;"
	"void main() {"
	"  vec4 texel = texture (basic_texture, texture_coordinates);"
	"  frag_color = texel;"
	"}";

const char * GLContext::texturedVertexShader =
	"#version 400\n"
	"layout(location = 0) in vec3 vp;"
	"uniform mat4 matrix;"
	"layout(location = 1) in vec2 vt;"
	"out vec2 texture_coordinates;"
	"void main () {"
	"   texture_coordinates = vt;"
	"   gl_Position = matrix * vec4 (vp, 1.0);"
	"}";




GLContext::GLContext(){}

GLContext::GLContext(HWND hwnd)
{
	create30Context(hwnd);
}

GLContext::~GLContext()
{
	wglMakeCurrent(_hdc, 0);
	wglDeleteContext(_hrc);
	ReleaseDC(_hwnd,_hdc);
	delete [] points;
}

bool GLContext::create30Context(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(_hdc, &pfd);
	if (nPixelFormat == 0)
		return false;

	bool bResult = SetPixelFormat(_hdc, nPixelFormat, &pfd);
	if (!bResult)
		return false;

	HGLRC tempContext = wglCreateContext(_hdc);
	wglMakeCurrent(_hdc, tempContext);

	if (glewInit() != GLEW_OK)
		return false;

	

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (glewIsSupported("WGL_ARB_create_context") == 1){
		_hrc =  wglCreateContextAttribsARB(_hdc, 0, attributes);
		wglMakeCurrent(0,0);
		wglDeleteContext(tempContext);
		wglMakeCurrent(_hdc, _hrc);
	}
	else
		_hrc = tempContext;

	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc (GL_LESS);

	return true;
}

void GLContext::setupScene()
{
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);

	//test
	points = new float[9];
	/*0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};*/

	points[0] = 0;
	points[1] = .5f;
	points[2] = 0;
	points[3] = .5f;
	points[4] = -.5f;
	points[5] = 0;
	points[6] = -.5f;
	points[7] = -.5f;
	points[8] = 0;



	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);

}

void GLContext::resize(int width, int height)
{
	_winWidth = width;
	_winHeight = height;
}

void GLContext::renderScene(CDrawList * list)
{
	glViewport(0,0, _winWidth, _winHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	int x = 0;
	while (!list->isEnd())
	{
		
		CSprite sprite = list->getSprite();
		unsigned int matrix = sprite.getMatrixLocation();
		glUseProgram(sprite.getShader());

		if (matrix != -1)
			glUniformMatrix4fv( matrix, 1, GL_FALSE, sprite.getMatrix().matrix);

		x = glGetError();
		glBindVertexArray(sprite.getVAO());
		x = glGetError();

		//glEnableVertexAttribArray (0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);

		if (!sprite.isNull())
		{
			glEnableVertexAttribArray (1);
			glActiveTexture(GL_TEXTURE0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)0);
			glBindTexture(GL_TEXTURE_2D, sprite.getTexID());
		}

		glDrawArrays(GL_TRIANGLES, 0, 6);
		x = glGetError();

		glDisableVertexAttribArray(1);
	}

	SwapBuffers(_hdc);
	x = glGetError();
}

//test purposes
void GLContext::renderScene(unsigned int shader)
{
	glViewport(0,0, _winWidth, _winHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SwapBuffers(_hdc);
	
}

