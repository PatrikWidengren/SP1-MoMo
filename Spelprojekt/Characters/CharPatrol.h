#ifndef INCLUDED_NPCPATROL
#define INCLUDED_NPCPATROL
#include "Character.h"

class CharPatrol : public Character{
public:
	//Write in turncount and movecount when ready in Map1
	CharPatrol(int arrX, int arrY, int **moves/*, int turnCount, int moveCount*/);
	virtual ~CharPatrol();//This is the X and Y position for the sprite
	virtual void reset();

	virtual intVector move();
	virtual intVector collide(intVector moves, int atPos);
	//This is the position in the array
	virtual int getX();
	virtual int getY();
	virtual int getLastX();
	virtual int getLastY();

	//Set X and Y in the array
	virtual void setX(int x);
	virtual void setY(int Y);
	virtual void setLast(float l);
	virtual float getLast();
	virtual float getType();
	//Get the time to spend animating each tiles movement
	virtual float getMoveTime();

	virtual void playAnimation();
	virtual void changeAnimation(int nr);

	static void initialize();
	static void finalize();
	virtual sf::Sprite* getSpriteSheet();
	//Treat this as running into and colliding with things?
	virtual bool getCollide();
private:
	int mArrayX, mArrayY, mLastX, mLastY;
	const coords mStartPos;
	const float mBaseType, mOrigLast;
	float mType, mLast, mMoveTime;
	//Path is a pointer because we don't want to copy mTurnCount0 ints per character.
	int **path;
	int mMoveCount, mTurnCount;
	//Single turn's worth of movement to retry in case of collision
	int *retryPath;
	int mTurnNo;
	bool walking = false;

	sf::Clock clock;
	thor::Animator<sf::Sprite, std::string> dogAnimator;
	sf::Texture mTextureSheet_dogWalk;
	sf::Texture mTextureSheet_dogIdle;
	sf::Sprite mDogIdleSheet;
	sf::Sprite mDogWalkSheet;
	sf::IntRect *mRect;

};

#endif