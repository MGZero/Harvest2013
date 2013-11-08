#ifndef CDRAWLIST_H
#define CDRAWLIST_H

#include <list>
#include <stdlib.h>
#include "CSprite.h"


class CDrawList : private std::list<CSprite>
{
public:
	CDrawList(){}
	void addSprite(CSprite);
	inline CSprite getSprite(){return *_current++;}
	void clearList();
	inline bool isEnd(){return empty() || _current == end();}

private:
	std::list<CSprite>::iterator _current;
};

#endif