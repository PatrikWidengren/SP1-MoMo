#ifndef INGAMEMENU
#define INGAMEMENU

#include "menu.h"

class inGameMenu :
	public Menu
{
public:
	inGameMenu(float width, float height);
	inGameMenu();
	~inGameMenu();

	// Load a backgrounds to show for the menu
	sf::Texture highlighttextBg01; //the highlightTexture for displaying.
	sf::Texture textBg01; //hold the texture

	sf::Texture textResume;
	sf::Texture textOption;
	sf::Texture textQuit;

	sf::Texture textHighlightResume;
	sf::Texture textHighlightOption;
	sf::Texture textHighlightQuit;

	sf::Sprite spriteResume;
	sf::Sprite spriteOption;
	sf::Sprite spriteQuit;

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	sf::Vector2i mMouse;

protected:
	static int const mNumberOfSelections = 3;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	int mState;
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