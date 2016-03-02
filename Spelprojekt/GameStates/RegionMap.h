#ifndef INCLUDED_REGIONMAP
#define INCLUDED_REGIONMAP

#include "Menu/menu.h"

struct RegionVariables {
	std::string BackgroundName= "Resource Files/Backgrounds/error.jpg";
	int levelCount = 0;
};

class RegionMap : public Menu
{
public:
	RegionMap(float width, float height);
	RegionMap();
	~RegionMap();
	bool reset = false;

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	static const int mMaxRegions = 3;
	
	sf::Texture textBackgrounds[mMaxRegions];

	sf::Texture textureShop;
	sf::Texture textArrow01;
	sf::Texture textHighlightArrow01;
	sf::Texture textMowers[2];
	sf::Texture textMowers[1];

	sf::Sprite spriteMower;
	sf::Sprite spriteHedgecutter;

	sf::Sprite spriteArrow01;
	sf::Sprite spriteArrow02;
	sf::Sprite spriteArrow03;
	sf::Sprite spriteArrow04;

	sf::Sprite spriteShop;

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();

	void setRegionState(int state);
	int checkRegionState();

protected:
	static int const mNumberOfSelections = 7;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	sf::Vector2i mMouse;
	int mState, mRegionState, mInternalState;
	RegionVariables mRegions[mMaxRegions];
	void changeInternalState(int newState);
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