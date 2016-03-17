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
#include "../Managers/AnimeManager.h"
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>
#include "../Static Objects/StaticObjects.h"
#include "../Characters/Character.h"
#include <map>

//Underklass till "Maps"
//Level 1
class Map1{
public:
	//Konstruktor som tar emot namnet p� sparfilen till arrayen
	Map1(std::string savefile, Player *m /*, std::string patrolPath*/);
	virtual ~Map1();
	//g�r mer eller mindra vad takeTurn brukade g�ra
	void update(SoundManager &sound, sf::RenderWindow &window);
	void beginTurn(int dir);
	void virtual render(sf::RenderWindow &window, AnimeManager &anime, sf::Vector2i &mouse);
	//Spawnar alla objekten, enligt array
	void virtual spawnObjects();
	//Returnerar objekten, detta beh�vs till main
	virtual std::vector<StaticObjects*> getObjects();
	//Returnerar spelaren, detta beh�vs till main
	virtual Player* getPlayer();
	int checkState();

	float** getGrid();
	//Returnerar npcs, detta beh�vs till main
	typedef std::map<coords, Character*> NpcMap;
	virtual NpcMap getNpcs();
	//Returnerar l�nga objekt, detta beh�vs till main
	virtual std::vector<StaticObjects*> getLongObjects();
	void deleteContent();
	//Funktion f�r att f� storleken p� arrayen, samt f� alla v�rden f�r medaljerna, denna funktion anropas i konstruktorn till Map
	void virtual getMapInfo();
	void resetGrid();
	void takeTurn(int dir, SoundManager &sound);
	int** getPatrolPath(int &skipLines);
	float** createGrid(int width, int height);
	//Added turn count
	int getTurnCount();
	int getMaxTurns();
	int getGrass();
	int getHedges();
	int getDandelions();
	std::vector<int> *getGoals();
	int mTurnCount = 0;
	int mLoseRounds = 50;
	int mWinRounds = 50;
	std::string mSavefile/*, mPatrolPath*/;
	//std::string getGrass();
private:
	/*Added helper functions for moving player and NPC to make code look better*/
	sf::IntRect *mRects[1];
	bool mClick = true;

	bool movePlayer(int dir, SoundManager &sound);
	bool moveNpc(int dir, int atPos, SoundManager &sound);
	bool mOngoingTurn = false;

	int mWidth, mHeight;
	int mBronzeGrass, mBronzeHedge, mBronzeDandelion;
	int mSilverGrass, mSilverHedge, mSilverDandelion;
	int mGoldGrass, mGoldHedge, mGoldDandelion;
	int mSkipLines = 0;
	int mState;
	float totalAmountOfGrass = 0;
	float totalAmountOfHedges = 0;
	float totalAmountOfDandelions = 0;
	int turnsLeft = 200;
	float cutGrass = 0;
	float cutHedges = 0;
	float cutDandelions = 0;
	int meepSpawnDirection;
	int specialFeature;
	int pushMapX, pushMapY;
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

	intVector mCurrentMove;
	int mPlaceInMove = 0, mNpcNo = 0;
	bool mMeepMoving = false, mNpcsMoving = false, mBreakMove;
	sf::Clock mTurnClock, mPlayerMoveTime, mNpcMoveTimer;
	float mNpcMoveTime;
	int mNextX, mNextY;
};


#endif