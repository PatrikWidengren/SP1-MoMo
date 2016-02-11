#ifndef INGAMEMENU
#define INGAMEMENU

#include "menu.h"
#define MAX_NUMBER_OF_SELECTIONS 3

class inGameMenu :
	public Menu
{
public:
	inGameMenu(float width, float height);
	inGameMenu();
	~inGameMenu();

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateInGameMenu(sf::RenderWindow &window);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	sf::Vector2i mMouse;

private:
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_SELECTIONS];
	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
};

#endif