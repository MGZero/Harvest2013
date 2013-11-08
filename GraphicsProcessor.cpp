#include "GraphicsProcessor.h"

const char * CGraphicsProcessor::_basicVertexShader =
	"#version 400\n"
	"in vec3 vp;"
	"uniform mat4 matrix;"
	"void main () {"
	"  gl_Position = matrix * vec4 (vp, 1.0);"
	"}";

const char * CGraphicsProcessor::_basicFragmentShader =
	"#version 400\n"
	"out vec4 frag_color;"
	"void main () {"
	"  frag_color = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";

unsigned int CGraphicsProcessor::_vs = 0;
unsigned int CGraphicsProcessor::_fs = 0;
unsigned int CGraphicsProcessor::_shaderProgram = 0;

CGraphicsProcessor::CGraphicsProcessor(HWND hwnd, int width, int height)
{
	_context = new GLContext(hwnd);
	_context->resize(width, height);
	_context->setupScene();
	_drawList = new CDrawList();
}

CGraphicsProcessor::~CGraphicsProcessor()
{
	delete _context;
	_context = nullptr;
	delete _drawList;
	_drawList = nullptr;
}

void CGraphicsProcessor::render(CMap * map)
{
	for (std::map<int, CLayer*>::iterator itr = map->_layers.begin(); itr != map->_layers.end(); itr++)
		for (std::unordered_map<std::string, CEntity*>::iterator entities = itr->second->_entities.begin(); entities != itr->second->_entities.end(); entities++)
			//if (!entities->second->isSpriteNull())
				_drawList->addSprite(entities->second->getSprite());

	_context->renderScene(_drawList);

	_drawList->clearList();
}

void CGraphicsProcessor::testDraw()
{
	_context->renderScene(_shaderProgram);
}

void CGraphicsProcessor::prepareShader()
{
	//basic vertex shader
	_vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vs, 1, &_basicVertexShader, 0);
	glCompileShader(_vs);

	//basic fragment shader
	_fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fs, 1, &_basicFragmentShader, 0);
	glCompileShader(_fs);

	//create and link shader program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vs);
	glAttachShader(_shaderProgram, _fs);
	glLinkProgram(_shaderProgram);

	

}