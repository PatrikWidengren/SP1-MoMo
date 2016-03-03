#ifndef INCLUDED_WORLDMAP
#define INCLUDED_WORLDMAP

#include "Menu/menu.h"

class WorldMap : public Menu
{
public:
	WorldMap(float width, float height);
	WorldMap();
	~WorldMap();
	bool reset = false;

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	int getRegion();
	void resetRegion();

	virtual void updateWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
protected:
	static int const mNumberOfSelections = 3;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	sf::Vector2i mMouse;
	int mState;
	int mRegion=0;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];

	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor för keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};


#endif