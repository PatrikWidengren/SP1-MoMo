#ifndef INCLUDED_MAP1
#define INCLUDED_MAP1
#include "Maps.h"
#include <SFML\Graphics.hpp>
#include "Grass.h"
#include "Stone.h"
#include "Fence.h"
#include "Player.h"
#include "Tree.h"
#include "GoLawnMower.h"
#include "RoyceMower.h"
#include "LawnMower.h"
#include "CharRand.h"
#include "CharPatrol.h"
#include <fstream>
#include <iomanip>
#include <vector>

//Underklass till "Maps"
//Level 1
class Map1 : public Maps{
public:
	//Konstruktor som tar emot namnet på sparfilen till arrayen
	Map1(std::string savefile);
	virtual ~Map1();
	void virtual render();
	//Spawnar alla objekten, enligt array
	void virtual spawnObjects();
	//Returnerar objekten, detta behövs till main
	virtual std::vector<StaticObjects*> getObjects();
	//Returnerar spelaren, detta behövs till main
	virtual Player* getPlayer();
	//Returnerar npcs, detta behövs till main
	virtual std::vector<Character*> getNpcs();
	//Returnerar långa objekt, detta behövs till main
	virtual std::vector<StaticObjects*> getLongObjects();
	//Funktion för att få storleken på arrayen, denna funktion anropas i konstruktorn till Map
	void virtual getArraySize();
	void takeTurn(int dir);
	float** createGrid(int width, int heigth);
private:
	//Added turn count
	int mTurnCount = 0;
	/*Added helper functions for moving player and NPC to make code look better*/
	bool movePlayer(int dir);
	bool moveNpc(int dir, int atPos);
	int mWidth, mHeigth;
	int totalAmountOfGrass = 0;
	int turnsLeft = 50;
	int cutGrass = 0;
	std::string mSavefile;
	float** mGrid;
	typedef std::vector<StaticObjects*> ObjectsVector;
	ObjectsVector mObjects;
	ObjectsVector mLongObjects;
	typedef std::vector<Character*> NpcVector;
	NpcVector mNpcs;
	Player* mPlayer;
	//Mower* lawnMower;

};


#endif