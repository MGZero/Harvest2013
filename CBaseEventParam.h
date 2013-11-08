#ifndef _CBASEEVENTPARAM_H_
#define _CBASEEVENTPARAM_H_

#include <stdlib.h>
#include <string>

class CBaseEventParam
{
public:
	CBaseEventParam(std::string name);
	CBaseEventParam(){}
	virtual ~CBaseEventParam();

	virtual void useValue() = 0;

private:
	std::string _name;
};

#endif