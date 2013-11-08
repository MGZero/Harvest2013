#include "CDrawList.h"

void CDrawList::addSprite(CSprite draw)
{
	push_back(draw);

	if (size() == 1)
		_current = begin();
}

void CDrawList::clearList()
{
	clear();
}