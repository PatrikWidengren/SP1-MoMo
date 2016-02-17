#ifndef INCLUDED_NPCRANDOM
#define INCLUDED_NPCRANDOM
#include "Character.h"

class CharRand : public Character{
public:
	/*Most of this is identical to the Player class. However, random movement
	character also needs to know how many steps it will take and if the
	direction should be locked between moves or not*/
	CharRand(int arrX, int arrY, float posX, float posY, int moveLength, bool lockDir);
	virtual ~CharRand();
	//This is the X and Y position for the sprite
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
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	//Treat this as running into and colliding with things?
	virtual bool getCollide();
private:
	int mArrayX, mArrayY, mSpeed;
	float mType, mLast, mPosX, mPosY;
	bool mDirLock;
	sf::Sprite mCharSprite;
};

#endif