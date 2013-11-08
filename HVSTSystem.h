#ifndef HVSTSYSTEM_H
#define HVSTSYSTEM_H

#include <string>
#include "CMap.h"

namespace HVSTSystem
{
	enum READMODE
	{
		disk = 0,
		memStream
	};

	void loadMap(std::string file, READMODE readmode = disk, bool cache = false);
};

#endif