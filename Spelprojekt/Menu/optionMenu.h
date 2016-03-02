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
	sf::Texture highlighttextBg01; //the highlightTexture for displaying.
	sf::Texture textBg01; //hold the texture

	sf::Texture sliderTextuer01; //hold the texture

	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	sf::Sprite slider01;

	sf::Texture textControl;
	sf::Texture textVideo;
	sf::Texture textAudio;
	sf::Texture textBack;

	sf::Texture textHighlightControl;
	sf::Texture textHighlightVideo;
	sf::Texture textHighlightAudio;
	sf::Texture textHighlightBack;

	sf::Sprite spriteControl;
	sf::Sprite spriteVideo;
	sf::Sprite spriteAudio;
	sf::Sprite spriteBack;


	virtual int checkState();
	virtual void updateoptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
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

