#ifndef INCLUDED_MAPS
#define INCLUDED_MAPS
#include "Static Objects/StaticObjects.h"
#include "Characters/Player.h"
#include "Characters/Character.h"
#include <vector>

//Basklass f�r alla banor
class Maps{
public:
	Maps();
	virtual ~Maps();
	void virtual render(sf::RenderWindow &window) = 0;
	void virtual spawnObjects() = 0;
	void virtual getMapInfo() = 0;
	virtual std::vector<StaticObjects*> getObjects() = 0;
	virtual Player* getPlayer() = 0;
	virtual std::vector<Character*> getNpcs() = 0;
	virtual std::vector<StaticObjects*> getLongObjects() = 0;

};

#endif