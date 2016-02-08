#ifndef INCLUDED_NPCPATROL
#define INCLUDED_NPCPATROL
#include "Character.h"

class CharPatrol : public Character{
public:
	//If the maximum amount of moves per turn changes, rewrite it in move() and constructor
	CharPatrol(int arrX, int arrY, float posX, float posY, int *moves[50][10]);
	virtual ~CharPatrol();
	virtual float getPosX();
	virtual float getPosY();
	virtual intVector move();
	virtual intVector collide(intVector moves, int atPos);
	virtual int getX();
	virtual int getY();
	virtual void setX(int x);
	virtual void setY(int Y);
	virtual void setLast(float l);
	virtual float getLast();
	virtual float getType();
	virtual void updPos(float x, float y);
	virtual void render();
	static void initialize();
	static void finalize();
	virtual sf::Sprite getSprite();
private:
	int mArrayX, mArrayY;
	float mType, mLast, mPosX, mPosY;
	int *path[50][10];
	int retryPath[10];
	int mTurnNo;
	sf::Sprite mCharSprite;
};

#endif