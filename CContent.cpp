#include "CContent.h"
#include <errno.h>

CSprite CContent::createSprite(std::string resourceName, vector3D coordinates)
{
	CSprite out(_sprites[resourceName], coordinates);
	return out;
}

void CContent::tearDown()
{
	for (std::unordered_map<std::string, FIBITMAP*>::iterator itr = _sprites.begin(); itr != _sprites.end(); itr++)
		FreeImage_Unload(itr->second);
	
	_sprites.clear();
}

const char * CContent::getShader(std::string shaderName)
{
	return _shaders[shaderName];
}

void CContent::init()
{
	//just load one image for now, testing only
	FILE * file = fopen("Resources\\Sprites\\zfgc.png", "rb");
	FreeImageIO io;
	

	//load the image data
	io.read_proc  = _readProc;
	io.write_proc = _writeProc;
	io.seek_proc  = _seekProc;
	io.tell_proc  = _tellProc;

	FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)file, 0);

	if (format != FIF_PNG)
		return;



	FIBITMAP * dib = FreeImage_LoadFromHandle(format, &io, (fi_handle)file, 0);
	fclose(file);
	_sprites.insert(std::pair<std::string, FIBITMAP *>("test", dib));

}

std::unordered_map<std::string, FIBITMAP *> CContent::_sprites = std::unordered_map<std::string, FIBITMAP *>();
std::unordered_map<std::string, const char *> CContent::_shaders = std::unordered_map<std::string, const char *>();