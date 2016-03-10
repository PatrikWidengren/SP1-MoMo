#ifndef OPTIONMENU
#define OPTIONMENU
#include "menu.h"
class optionMenu :
	public Menu
{
public:
	optionMenu(float width, float height);
	optionMenu();
	~optionMenu();
	// Load a backgrounds to show for the menu
	sf::Texture* highlighttextBg01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture(); //hold the texture

	sf::Texture* sliderTextuer01 = new sf::Texture(); //hold the texture

	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	sf::Sprite* slider01 = new sf::Sprite();

	sf::Texture* textControl = new sf::Texture();
	sf::Texture* textVideo = new sf::Texture();
	sf::Texture* textAudio = new sf::Texture();
	sf::Texture* textBack = new sf::Texture();

	sf::Texture* textHighlightControl = new sf::Texture();
	sf::Texture* textHighlightVideo = new sf::Texture();
	sf::Texture* textHighlightAudio = new sf::Texture();
	sf::Texture* textHighlightBack = new sf::Texture();

	sf::Sprite* spriteControl = new sf::Sprite();
	sf::Sprite* spriteVideo = new sf::Sprite();
	sf::Sprite* spriteAudio = new sf::Sprite();
	sf::Sprite* spriteBack = new sf::Sprite();


	virtual int checkState();
	virtual void updateoptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
	sf::Vector2i mMouse;

	int checkOptionState();

protected:
	static int const mNumberOfSelections = 4;

private:
	int maxSliderX;
	int minSliderX;
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
};
#endif

