#ifndef INCLUDED_NPCPATROL
#define INCLUDED_NPCPATROL
#include "Character.h"

class CharPatrol : public Character{
public:
	//If the maximum amount of moves per turn changes, rewrite it in move() and constructor
	CharPatrol(int arrX, int arrY, float posX, float posY, int **moves);
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
	/*Update coordinates for the sprite. x and y is value the position has
	changed by*/
	virtual void updPos(float x, float y);
	virtual void render();
	static void initialize();
	static void finalize();
	virtual sf::Sprite getSprite();
private:
	int mArrayX, mArrayY;
	float mType, mLast, mPosX, mPosY;
	//Path is a pointer because we don't want to copy 500 ints per character.
	int **path;
	//Single turn's worth of movement to retry in case of collision
	int retryPath[10];
	int mTurnNo;
	sf::Sprite mCharSprite;
};

#endif