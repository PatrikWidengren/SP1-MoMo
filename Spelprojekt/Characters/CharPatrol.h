#ifndef INCLUDED_NPCPATROL
#define INCLUDED_NPCPATROL
#include "Character.h"

class CharPatrol : public Character{
public:
	//Write in turncount and movecount when ready in Map1
	CharPatrol(int arrX, int arrY, float posX, float posY, int **moves/*, int turnCount, int moveCount*/);
	virtual ~CharPatrol();//This is the X and Y position for the sprite
	virtual float getPosX();
	virtual float getPosY();
	virtual intVector move();
	virtual intVector collide(intVector moves, int atPos);
	//This is the position in the array
	virtual int getX();
	virtual int getY();
	//Set X and Y in the array
	virtual void setX(int x);
	virtual void setY(int Y);
	virtual void setLast(float l);
	virtual float getLast();
	virtual float getType();
	virtual bool getDoneMoving();
	virtual void swapDoneMoving();
	/*Update coordinates for the sprite. x and y is value the position has
	changed by*/
	virtual void updPos(float x, float y);
	virtual void render();
	static void initialize();
	static void finalize();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	//Treat this as running into and colliding with things?
	virtual bool getCollide();
private:
	bool mDoneMoving = false;
	int mArrayX, mArrayY;
	float mType, mLast, mPosX, mPosY;
	//Path is a pointer because we don't want to copy mTurnCount0 ints per character.
	int **path;
	int mMoveCount, mTurnCount;
	//Single turn's worth of movement to retry in case of collision
	int *retryPath;
	int mTurnNo;
	sf::Sprite mCharSprite;
};

#endif