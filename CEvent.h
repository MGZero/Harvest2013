#ifndef _CEVENT_H_
#define _CEVENT_H_

#include <list>
#include "CEntity.h"
#include <functional>
#include <boost/variant.hpp>
#include "lib/OIS/OISKeyboard.h"

typedef boost::variant<int, float, char, std::string, std::vector<OIS::KeyCode>, CEntity*> params;
typedef std::list<params> paramList;

class CEvent
{
public:
	//I swear, if this shit isn't cleaned up properly, I'm going to kill a small cow.
	//allocate the array in the caller
	CEvent(CEntity * sender); 
	CEvent(){}
	virtual ~CEvent(){};

	virtual void process() = 0;

protected:
	paramList _parameterList;
	CEntity * _sender;

};


#endif