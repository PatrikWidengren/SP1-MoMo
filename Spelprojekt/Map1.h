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
#include "CharRand.h"
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
	virtual std::vector<Character*> getNpcs();
	void virtual getArraySize();
	void takeTurn(int dir);
	float** createGrid(int width, int heigth);
private:
	/*Added helper functions for moving player and NPC to make code look better*/
	bool movePlayer(int dir);
	bool moveNpc(int dir, int atPos);
	int mWidth, mHeigth;
	std::string mSavefile;
	float** mGrid;
	typedef std::vector<StaticObjects*> ObjectsVector;
	ObjectsVector mObjects;
	typedef std::vector<Character*> NpcVector;
	NpcVector mNpcs;
	Player* mPlayer;
	//Mower* lawnMower;

};


#endif