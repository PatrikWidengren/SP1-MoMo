#ifndef STARTMENU
#define STARTMENU

#include "menu.h"

class startMenu : public Menu
{
public:
	startMenu(float width, float height);
	startMenu();
	~startMenu();
	bool reset = false;

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
protected:
	static int const mNumberOfSelections = 3;

private:
	sf::Vector2i mMouse;


	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];
	sf::IntRect *mRects[mNumberOfSelections];

	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor f�r keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};


#endif