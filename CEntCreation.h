#ifndef CENTCREATION_H
#define CENTCREATION_H

#include <string>

class CEntCreation
{
public:
	CEntCreation(std::string entityType, std::string name, int x, int y, int layer) : _entityType(entityType), _name(name), _x(x), _y(y), _layer(layer){}
	CEntCreation(){}
	~CEntCreation(){};

	inline std::string getType(){return _entityType;}
	inline std::string getName(){return _name;}
	inline int x(){return _x;}
	inline int y(){return _y;}
	inline int layer(){return _layer;}

private:
	std::string _entityType;
	std::string _name;
	int _x;
	int _y;
	int _layer;
};

#endif