#ifndef INCLUDED_MAP1
#define INCLUDED_MAP1
#include "Maps.h"
#include <SFML\Graphics.hpp>
#include "Static Objects/Grass.h"
#include "Static Objects/Stone.h"
#include "Static Objects/Fence.h"
#include "Static Objects/Tree.h"
#include "Static Objects/Hedge.h"
#include "Characters/Player.h"
#include "Tools/Lawnmower/GoLawnMower.h"
#include "Tools/Lawnmower/RoyceMower.h"
#include "Tools/Lawnmower/LawnMower.h"
#include "Tools/Hedge Cutter/HedgeCutter.h"
#include "Characters/CharRand.h"
#include "Characters/CharPatrol.h"
#include "SoundManager.h"
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>

//Underklass till "Maps"
//Level 1
class Map1 : public Maps{
public:
	//Konstruktor som tar emot namnet p� sparfilen till arrayen
	Map1(std::string savefile);
	virtual ~Map1();
	void virtual render(sf::RenderWindow &window);
	//Spawnar alla objekten, enligt array
	void virtual spawnObjects();
	//Returnerar objekten, detta beh�vs till main
	virtual std::vector<StaticObjects*> getObjects();
	//Returnerar spelaren, detta beh�vs till main
	virtual Player* getPlayer();

	float** Map1::getGrid();
	//Returnerar npcs, detta beh�vs till main
	virtual std::vector<Character*> getNpcs();
	//Returnerar l�nga objekt, detta beh�vs till main
	virtual std::vector<StaticObjects*> getLongObjects();
	void deleteContent();
	//Funktion f�r att f� storleken p� arrayen, samt f� alla v�rden f�r medaljerna, denna funktion anropas i konstruktorn till Map
	void virtual getMapInfo();
	void takeTurn(int dir, SoundManager &sound);
	float** createGrid(int width, int heigth);
	//Added turn count
	int mTurnCount = 0;
	int mLoseRounds = 50;
	int mWinRounds = 40;
private:
	/*Added helper functions for moving player and NPC to make code look better*/
	bool movePlayer(int dir, SoundManager &sound);
	bool moveNpc(int dir, int atPos, SoundManager &sound);
	//int patrolPath[50][10] = {};
	int mWidth, mHeigth;
	int mBronzeGrass, mBronzeHedge;
	int mSilverGrass, mSilverHedge;
	int mGoldGrass, mGoldHedge;
	int totalAmountOfGrass = 0;
	int totalAmountOfHedges = 0;
	int turnsLeft = 50;
	int cutGrass = 0;
	int cutHedges = 0;
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