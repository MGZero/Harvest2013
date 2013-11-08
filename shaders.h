#ifndef SHADERS_H
#define SHADERS_H

namespace shaders
{
	static const char * texturedFragmentShader = 
		"#version 400\n"
		"out vec4 frag_color;"
		"uniform sampler2D basic_texture;"
		"void main () {"
		"  frag_color = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";
};

#endif