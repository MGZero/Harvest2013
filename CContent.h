#ifndef CCONTENT_H
#define CCONTENT_H

//#include "FreeImage.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include "CSprite.h"
//#include "Vector3D.h"

class CContent
{
public:
	static CSprite createSprite(std::string resourceName, vector3D coordinates);
	static const char * getShader(std::string shaderName);
	static void tearDown();
	static void init();

private:
	static std::unordered_map<std::string, FIBITMAP *> _sprites;
	static std::unordered_map<std::string, const char *> _shaders;

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