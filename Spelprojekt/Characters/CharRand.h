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

	virtual int move();
	virtual int getMove(int i);
	virtual intVector collide(int atPos);
	//This is the position in the array
	virtual int getX();
	virtual int getY();
	virtual int getLastX();
	virtual int getLastY();

	virtual void setWalking(bool walk);
	virtual bool getWalking();
	virtual bool getMoveBroke();
	virtual sf::Clock getMoveClock();
	virtual void resetMoveClock();

	//Set X and Y in the array
	virtual void setX(int x);
	virtual void setY(int Y);
	virtual void setLast(float l);
	virtual float getLast();
	virtual float getType();
	//Get the time to spend animating each tiles movement
	virtual float getMoveTime();


	static void initialize();
	static void finalize();
	virtual sf::Sprite* getSpriteSheet();
	virtual void changeAnimation(int nr);
	virtual void playAnimation();
	virtual void scale(sf::RenderWindow &window);

	//Treat this as running into and colliding with things?
	virtual bool getCollide();
private:
	bool mDoneMoving = false;
	int mArrayX, mArrayY, mSpeed, mLastX, mLastY;
	const coords mStartPos;
	const float mBaseType, mOrigLast;
	float mType, mLast, mMoveTime;
	bool mDirLock;
	bool mBreakMove = false;
	bool walking = false;
	intVector mMovement;

	sf::Clock clock;
	sf::Clock mMoveClock;
	thor::Animator<sf::Sprite, std::string>* catAnimator = new thor::Animator<sf::Sprite, std::string>;
	sf::Texture* mTextureSheet_catIdle = new sf::Texture;
	sf::Texture* mTextureSheet_catWalk = new sf::Texture;
	sf::Sprite* mCatIdleSheet = new sf::Sprite;
	sf::Sprite* mCatWalkSheet = new sf::Sprite;
	sf::IntRect *mRect;
};

#endif