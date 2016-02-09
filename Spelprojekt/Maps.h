#ifndef INCLUDED_MAPS
#define INCLUDED_MAPS
#include "StaticObjects.h"
#include "Player.h"
#include "Character.h"
#include <vector>

//Basklass för alla banor
class Maps{
public:
	Maps();
	virtual ~Maps();
	void virtual render() = 0;
	void virtual spawnObjects() = 0;
	void virtual getArraySize() = 0;
	virtual std::vector<StaticObjects*> getObjects() = 0;
	virtual Player* getPlayer() = 0;
	virtual std::vector<Character*> getNpcs() = 0;
	virtual std::vector<StaticObjects*> getLongObjects() = 0;

};

#endif