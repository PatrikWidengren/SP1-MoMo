#ifndef INCLUDED_MENU
#define INCLUDED_MENU
#include <SFML\Graphics.hpp>
#include "../../Managers/SoundManager.h"
#include <string>
#include <iostream>

class Menu
{
public:
	Menu();

	~Menu();

	// Load a backgrounds to show for the menu
	sf::Texture* highlighttextBg01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture(); //hold the texture

	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	virtual int checkState() = 0;
	virtual void displayMenu01(sf::RenderWindow &window) = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
protected:
	static int const mNumberOfSelections = 3;
	bool mClick=false;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	sf::Vector2i mMouse;
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];
	virtual void setTextures() = 0; //Set a texture to a sprite
	virtual void setFonts() = 0;

};



#endif

