#ifndef WINMENU
#define WINMENU

#include "menu.h"

class WinMenu :
	public Menu
{
public:
	WinMenu(float width, float height);
	WinMenu();
	~WinMenu();
	bool reset = false;
	// Load a backgrounds to show for the menu
	sf::Texture highlighttextBg01; //the highlightTexture for displaying.
	sf::Texture textBg01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
	sf::Vector2i mMouse;

protected:
	static int const mNumberOfSelections = 2;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];
	sf::Text mCompleteText;
	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor f�r keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};

#endif