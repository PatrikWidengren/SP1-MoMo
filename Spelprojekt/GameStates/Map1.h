#ifndef INCLUDED_MAP1
#define INCLUDED_MAP1
#include "Maps.h"
#include <SFML\Graphics.hpp>
#include "../Static Objects/Grass.h"
#include "../Static Objects/Stone.h"
#include "../Static Objects/Fence.h"
#include "../Static Objects/Tree.h"
#include "../Static Objects/Hedge.h"
#include "../Static Objects/Dandelion.h"
#include "../Static Objects/Gravel.h"
#include "../Static Objects/Fountain.h"
#include "../Characters/Player.h"
#include "../Tools/Lawnmower/GoLawnMower.h"
#include "../Tools/Lawnmower/RoyceMower.h"
#include "../Tools/Lawnmower/LawnMower.h"
#include "../Tools/Hedge Cutter/HedgeCutter.h"
#include "../Characters/CharRand.h"
#include "../Characters/CharPatrol.h"
#include "../Managers/SoundManager.h"
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>

//Underklass till "Maps"
//Level 1
class Map1 : public Maps{
public:
	//Konstruktor som tar emot namnet på sparfilen till arrayen
	Map1(std::string savefile, Player *m, std::string patrolPath);
	virtual ~Map1();
	void virtual render(sf::RenderWindow &window);
	//Spawnar alla objekten, enligt array
	void virtual spawnObjects();
	//Returnerar objekten, detta behövs till main
	virtual std::vector<StaticObjects*> getObjects();
	//Returnerar spelaren, detta behövs till main
	virtual Player* getPlayer();

	float** getGrid();
	//Returnerar npcs, detta behövs till main
	virtual NpcMap getNpcs();
	//Returnerar långa objekt, detta behövs till main
	virtual std::vector<StaticObjects*> getLongObjects();
	void deleteContent();
	//Funktion för att få storleken på arrayen, samt få alla värden för medaljerna, denna funktion anropas i konstruktorn till Map
	void virtual getMapInfo();
	void resetGrid();
	void takeTurn(int dir, SoundManager &sound);
	int** getPatrolPath(int &skipLines);
	float** createGrid(int width, int height);
	//Added turn count
	int mTurnCount = 0;
	int mLoseRounds = 50;
	int mWinRounds = 40;
private:
	/*Added helper functions for moving player and NPC to make code look better*/
	bool movePlayer(int dir, SoundManager &sound);
	bool moveNpc(int dir, int atPos, SoundManager &sound);
	int mWidth, mHeight;
	int mBronzeGrass, mBronzeHedge, mBronzeDandelion;
	int mSilverGrass, mSilverHedge, mSilverDandelion;
	int mGoldGrass, mGoldHedge, mGoldDandelion;
	int mSkipLines = 0;
	float totalAmountOfGrass = 0;
	float totalAmountOfHedges = 0;
	float totalAmountOfDandelions = 0;
	int turnsLeft = 50;
	float cutGrass = 0;
	float cutHedges = 0;
	float cutDandelions = 0;
	int meepSpawnDirection;
	int specialFeature;
	std::string mSavefile, mPatrolPath;
	float** mGrid;
	typedef std::vector<StaticObjects*> ObjectsVector;
	ObjectsVector mObjects;
	ObjectsVector mLongObjects;
	typedef std::vector<Character*> NpcVector;
	NpcVector mNpcVector;
	std::vector<coords> mNpcCoords;
	NpcMap mNpcs;
	Player* mPlayer;
	//Mower* lawnMower;

};


#endif