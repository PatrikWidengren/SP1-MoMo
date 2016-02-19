#ifndef KEYBOARDOPTIONMENU
#define KEYBOARDOPTIONMENU

#include "Menu\menu.h"

class KeyboardOptionMenu : public Menu
{
public:
	KeyboardOptionMenu(float width, float height);
	KeyboardOptionMenu();
	~KeyboardOptionMenu();

	// Load a backgrounds to show for the menu
	sf::Texture highlightTexture01; //the highlightTexture for displaying.
	sf::Texture texture01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateKeyboardOptionMenu(sf::RenderWindow &window);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	sf::Vector2i mMouse;

protected:
	static int const mNumberOfSelections = 3;

private:
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];
	sf::Text mText01;

	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor för keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};

#endif