#ifndef INCLUDED_FOUNTAIN
#define INCLUDED_FOUNTAIN

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Fountain : public StaticObjects {
public:
	Fountain(int arrayX, int arrayY, float posX, float posY);
	virtual ~Fountain();
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
	sf::Sprite mSprite;
};

#endif