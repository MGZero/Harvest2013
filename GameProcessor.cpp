#include "GameProcessor.h"

int CGameProcessor::_winHeight = 600;
int CGameProcessor::_winWidth = 800;
std::string CGameProcessor::_winTitle = "Harvest Engine 2013";

CGameProcessor::CGameProcessor(OIS::ParamList pl)
{

	std::ifstream config("cfg/config.cfg", std::ios::in);
	std::list<std::string> events;
	std::list<std::string> sysEvents;

	std::regex regex("^[a-zA-Z0-9:]{1,1}[a-zA-Z0-9:= ]*$");

	enum MODE
	{
		nada = 0,
		glblEv,
		sysEv,
		cvars,
		localEv
	};

	MODE mode = nada;

	while (!config.eof())
	{
		//look for a line starting with ::
		std::string input = "";

		std::getline(config, input);

		//are there comments?
		int x = 0;

		

		input = boost::trim_left_copy(input);
		input = boost::trim_right_copy(input);

		if (input.substr(0,2) == "::")
		{
				//check what we're looking at
				if (input.substr(2, input.length() - 2) == "GLOBALEVENTS")
					mode = glblEv;	
				else if(input.substr(2, input.length() - 2) == "SYSEVENTS")
					mode = sysEv;
				else if (input.substr(2, input.length() - 2) == "CVARS")
					mode = cvars;
				else if (input.substr(2, input.length() - 2) == "LOCALEVENTS")
					mode = localEv;

				continue;
		}
		
		//hold the fucking phone, is this line malformed?
		if(!std::regex_match(input,regex))
			continue; //nope, don't want that shit

		
		switch (mode)
		{
		case glblEv:
			events.push_front(input);
			break;

		case localEv:
			CEntity::addLocalEvent(input);
			break;

		case sysEv:
			sysEvents.push_front(input);
			break;

		case cvars:
			x = input.find('=',0) + 1;

			if (input.find("winWidth",0) == 0)
				_winWidth = atoi(input.substr(x, input.length() - x).c_str());
			else if (input.find("winHeight",0) == 0)
				_winHeight = atoi(input.substr(x, input.length() - x).c_str());
			else if (input.find("winTitle",0) == 0)
				_winTitle = input.substr(x, input.length() - x).c_str();
			
			break;

		default:
			break;
		}
		
	}

	config.close();
	_eventProcessor = new CEventProcessor(events, sysEvents, pl);
	

}

CMap CGameProcessor::getCurrentMap()
{
	return _eventProcessor->getCurrentMap();
}

CGameProcessor::~CGameProcessor()
{
	delete _eventProcessor;
	_eventProcessor = nullptr;
}

void CGameProcessor::run()
{
	_eventProcessor->process();
}

int CGameProcessor::getWinHeight()
{
	return _winHeight;
}

std::string CGameProcessor::getWinTitle()
{
	return _winTitle;
}

int CGameProcessor::getWinWidth()
{
	return _winWidth;
}

void CGameProcessor::setCurrentMap(CMap * map)
{
	_eventProcessor->setCurrentMap(map);
}

