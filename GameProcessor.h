#ifndef _GAMEPROCESSOR_H_
#define _GAMEPROCESSOR_H_

#include <fstream>
#include <iostream>
#include <map>
#include "EventProcessor.h"
#include "MapProcessor.h"
#include <boost/algorithm/string.hpp>
#include <regex>
#include <algorithm>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ENTITYCFG "entities\\config.cfg"

class CGameProcessor
{
public:
	void run();
	CGameProcessor(OIS::ParamList pl);
	virtual ~CGameProcessor();

	static int getWinHeight();
	static int getWinWidth();
	static std::string getWinTitle();
	inline bool quit(){return _eventProcessor->quitGame();}
	CMap getCurrentMap();

	//test only
	void setCurrentMap(CMap * map);

private:
	
	//no implementation -- do not use
	CGameProcessor(const CGameProcessor &);
	CGameProcessor & operator= (const CGameProcessor &);

	static CGameProcessor * _singleton;
	CEventProcessor * _eventProcessor;
	static int _winWidth;
	static int _winHeight;
	static std::string _winTitle;
};

#endif