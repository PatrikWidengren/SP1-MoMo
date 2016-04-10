#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER
#include "..\Tools\Lawnmower\BaseMower.h"
#include "SFML\Graphics.hpp"
#include "Thor\Animations.hpp"
#include "..\Tools\Hedge Cutter\BaseShears.h"

class Player{
public:
	/*X and Y position for the array, a lawnmower, and the X and Y coordinates*/
	Player(Mower *m, Shears *c/*, float posX, float posY*/);
	~Player();
	/*Return movement as intvector*/
	intVector move(int dir);
	//float getPosX();
	//float getPosY();
	/*collision during movement "moves" at position "atPos"*/
	void collide(intVector moves, int atPos);
	void collideWith(int dmg);

	virtual void setWalking(bool walk);
	virtual bool getWalking();
	//Get array position
	int getX();
	int getY();
	int getLastX();
	int getLastY();

	/*Set Players X value in the array*/
	void setX(int x);
	/*Set Players Y value in the array*/
	void setY(int y);
	/*Three functions that only serve to help the takeTurn function in Map*/
	/*Save the value of the value in the array position Meep is moving into*/
	void setLast(float l);
	/*Return the value that was in the position Meep currently occupies*/
	float getLast();
	/*Get the Player's type (the int that represents it in the array)*/
	float getType();
	//Get the time to spend animating each tiles movement
	float getMoveTime();

	//true if equipped lawnmower, false if hedge cutter
	bool getMowerEquipped();
	bool getFunctioning();
	//Swap which tool is equipped;
	void swapEquipped();
	//get the string for the currently equipped tool
	std::string getMower();
	std::string getShears();
	//Set which lawnmower or hedge cutter is being used
	void setMower(Mower *m, int i);
	void setHedgeTool(Shears *s, int i);
	cutVector getCuts();
	void changeAnimation(int nr);
	void playPlayer();
	sf::Sprite* getSpriteSheet();
	void scale(sf::RenderWindow &window);
	int mdopies; // . . . . . . . . . . . . Valuta
	Mower* mower();

	void reset();

private:
	sf::Clock moveClock;
	sf::Clock clock;
	thor::Animator<sf::Sprite, std::string>* animatorMeep = new thor::Animator<sf::Sprite, std::string>;
	sf::Texture* mTextureIdleSheet1 = new sf::Texture;
	sf::Texture* mTextureWalkSheet1 = new sf::Texture;
	sf::Texture* mTextureIdleSheet2 = new sf::Texture;
	sf::Texture* mTextureWalkSheet2 = new sf::Texture;
	sf::Texture* mTextureIdleSheet3 = new sf::Texture;
	sf::Texture* mTextureWalkSheet3 = new sf::Texture;
	sf::Texture* mTextureIdleSheet4 = new sf::Texture;
	sf::Texture* mTextureWalkSheet4 = new sf::Texture;
	sf::Texture* mTextureIdleSheet5 = new sf::Texture;
	sf::Texture* mTextureWalkSheet5 = new sf::Texture;
	sf::Texture* mTextureIdleSheetCutter1 = new sf::Texture;
	sf::Texture* mTextureWalkSheetCutter1 = new sf::Texture;
	sf::Sprite* mSpriteIdleSheet = new sf::Sprite;
	sf::Sprite* mSpriteWalkSheet = new sf::Sprite;
	sf::IntRect *mRect;
	/*equipped lawnmower*/
	Mower *mLawnMower, *mAntiLeakMower;
	Shears *mHedgeTool, *mAntiLeakHedgeTool;
	//When hedge cutter is equipped, this value is false
	bool mMowerEquipped = true;
	bool walking = false;;
	int intMower = 0;
	int intCutter = 0;
	/*x and y in the array*/
	int mArrayX = 0, mArrayY = 0, mLastX = 0, mLastY = 0;
	/*important values for the array*/
	const float mBaseType;
	float mType, mLast, mMoveTime;
	/*x and y coordinates for sprite*/
	//float mPosX, mPosY;
	/*sprite*/
	//sf::Sprite mPlayerSprite;
};

#endif