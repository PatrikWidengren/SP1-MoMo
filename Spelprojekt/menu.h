#ifndef INCLUDED_MENU
#define INCLUDED_MENU
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

#define MAX_NUMBER_OF_SELECTIONS 3

class Menu
{
public:
	Menu();
	
	~Menu();

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.
	
	virtual int checkState() = 0;
	virtual void displayMenu01(sf::RenderWindow &window) = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	sf::Vector2i mMouse;

private:
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_SELECTIONS];
	virtual void setTextures() = 0; //Set a texture to a sprite
	virtual void setFonts() = 0;

};



#endif

