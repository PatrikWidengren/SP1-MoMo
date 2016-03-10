#ifndef INCLUDED_GRASS
#define INCLUDED_GRASS

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Grass : public StaticObjects{
public:
	Grass(int arrayX, int arrayY, float posX, float posY);
	virtual ~Grass();
	virtual void render();
	virtual float getPosX();
	virtual float getPosY();
	virtual int getArrayX();
	virtual int getArrayY();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	virtual void setCut();
	virtual bool getCut();

	static void initialize();
	static void finalize();
private:
	bool isCut = false;
	float mPosX, mPosY;
	int mArrayX, mArrayY;
	sf::Sprite* mSprite = new sf::Sprite;
};

#endif