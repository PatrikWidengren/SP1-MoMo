#pragma once
#include "menu.h"


class VideoOptionMenu : public Menu
{
public:
	VideoOptionMenu(float width, float height);
	~VideoOptionMenu();

	// Load a backgrounds to show for the menu
	sf::Texture* textCheckBox = new sf::Texture; 
	sf::Texture* textBg01 = new sf::Texture;

	sf::Texture* textInGameOption = new sf::Texture;

	sf::Texture* textBack = new sf::Texture;
	sf::Texture* textHighlightBack = new sf::Texture;

	sf::Sprite* spriteCheckbox01 = new sf::Sprite;
	sf::Sprite* spriteCheckbox02 = new sf::Sprite;

	sf::Sprite* spriteBack = new sf::Sprite;

	sf::Sprite* spriteBg01 = new sf::Sprite;
	sf::Sprite* spriteIngameOption = new sf::Sprite;

	virtual int checkState();
	virtual void updateVideoOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
	sf::Vector2i mMouse;

	int checkOptionState();

protected:
	static int const mNumberOfSelections = 3;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	int mOptionMenuState;
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
	bool mFullscreen = false;
};