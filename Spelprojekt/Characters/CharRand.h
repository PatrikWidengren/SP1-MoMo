#ifndef INCLUDED_NPCRANDOM
#define INCLUDED_NPCRANDOM
#include "Character.h"

class CharRand : public Character{
public:
	/*Most of this is identical to the Player class. However, random movement
	character also needs to know how many steps it will take and if the
	direction should be locked between moves or not*/
	CharRand(int arrX, int arrY, int moveLength, bool lockDir);
	virtual ~CharRand();
	virtual void reset();

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

	virtual void render();
	static void initialize();
	static void finalize();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	//Treat this as running into and colliding with things?
	virtual bool getCollide();
private:
	bool mDoneMoving = false;
	int mArrayX, mArrayY, mSpeed;
	const coords mStartPos;
	const float mBaseType;
	float mType, mLast;
	bool mDirLock;
	sf::Sprite mCharSprite;
};

#endif