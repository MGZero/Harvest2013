#ifndef _CEVENTPARAM_H_
#define _CEVENTPARAM_H_

#include "CBaseEventParam.h"

template <class T>
class CEventParam : public CBaseEventParam
{
public:
	CEventParam(std::string name, T data) : CBaseEventParam(name), _data(data){}
	CEventParam(){}
	~CEventParam(){}

	void useValue(){}

private:
	T _data;
};

#endif