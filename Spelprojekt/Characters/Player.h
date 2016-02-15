#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER
#include "..\Tools\Lawnmower\BaseMower.h"
#include "SFML\Graphics.hpp"
#include "..\Tools\Hedge Cutter\BaseShears.h"

class Player{
public:
	/*X and Y position for the array, a lawnmower, and the X and Y coordinates*/
	Player(int arrX, int arrY, Mower *m, Shears *c, float posX, float posY);
	~Player();
	/*Return movement as intvector*/
	intVector move(int dir);
	float getPosX();
	float getPosY();
	/*collision during movement "moves" at position "atPos"*/
	void collide(intVector moves, int atPos);
	void collideWith(int dmg);
	/*Get Player's X value from the array*/
	int getX();
	/*Get Player's Y value from the array*/
	int getY();
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
	//true if equipped lawnmower, false if hedge cutter
	bool getMowerEquipped();
	//Swap which tool is equipped;
	void swapEquipped();
	//get the string for the currently equipped tool
	std::string getMower();
	std::string getShears();
	//Set which lawnmower or hedge cutter is being used
	void setMower(Mower *m);
	void setHedgeTool(Shears *s);
	cutVector getCuts();
	/*update the position of the sprite by +x, +y*/
	void updPos(float x, float y);
	//void update();
	void render();
	static void initialize();
	static void finalize();
	sf::Sprite getSprite();
private:
	/*equipped lawnmower*/
	Mower *mLawnMower, *mAntiLeakMower;
	Shears *mHedgeTool, *mAntiLeakHedgeTool;
	//When hedge cutter is equipped, this value is false
	bool mMowerEquipped = true;
	/*x and y in the array*/
	int mArrayX, mArrayY;
	/*important values for the array*/
	float mType, mLast;
	/*x and y coordinates for sprite*/
	float mPosX, mPosY;
	/*sprite*/
	sf::Sprite mPlayerSprite;
};

#endif