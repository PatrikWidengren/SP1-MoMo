#ifndef INCLUDED_MAP1
#define INCLUDED_MAP1
#include "Maps.h"
#include <SFML\Graphics.hpp>
#include "Grass.h"
#include "Stone.h"
#include "Fence.h"
#include "Player.h"
#include "GoLawnMower.h"
#include "RoyceMower.h"
#include "LawnMower.h"
#include <fstream>
#include <iomanip>
#include <vector>

//Underklass till "Maps"
//Level 1
class Map1 : public Maps{
public:
	Map1(std::string savefile);
	virtual ~Map1();
	void virtual render();
	void virtual spawnObjects();
	virtual std::vector<StaticObjects*> getObjects();
	virtual Player* getPlayer();
	void virtual getArraySize();
	void takeTurn(int dir);
	float** createGrid(int width, int heigth);
private:
	int mWidth, mHeigth;
	std::string mSavefile;
	float** mGrid;
	typedef std::vector<StaticObjects*> ObjectsVector;
	ObjectsVector mObjects;
	Player* mPlayer;
	//Mower* lawnMower;

};


#endif