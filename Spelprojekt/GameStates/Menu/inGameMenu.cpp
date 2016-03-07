#include "inGameMenu.h"

inGameMenu::inGameMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 2;
	setFonts();
	setTextures();

	spriteResume.setPosition(700, 550);
	spriteOption.setPosition(700, 730);
	spriteQuit.setPosition(700, 900);

	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(643, 546), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(643, 725), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(643, 896), sf::Vector2i(550, 100));

}

inGameMenu::~inGameMenu()
{
}

void inGameMenu::updateInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteResume.setTexture(textHighlightResume);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mState = 1;
		}
	}
	else
		spriteResume.setTexture(textResume);

	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteOption.setTexture(textHighlightOption);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mState = 4;
		}
	}
	else
		spriteOption.setTexture(textOption);

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteQuit.setTexture(textHighlightQuit);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mState = 3;

		}
	}
	else
		spriteQuit.setTexture(textQuit);


	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void inGameMenu::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	window.draw(spriteResume);
	window.draw(spriteOption);
	window.draw(spriteQuit);

}

void inGameMenu::setTextures()
{
	
	if (!textBg01.loadFromFile("Resource Files/Backgrounds/Background_ESC.png")) //try to load the texture. if its wrong, give error
	textBg01.loadFromFile("error.jpg");

	if (!highlighttextBg01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	highlighttextBg01.loadFromFile("error.jpg");



	if (!textResume.loadFromFile("Resource Files/Menus/resume.png")) //try to load the texture. if its wrong, give error
		textResume.loadFromFile("error.jpg");
	if (!textOption.loadFromFile("Resource Files/Menus/options.png")) //try to load the texture. if its wrong, give error
		textOption.loadFromFile("error.jpg");
	if (!textQuit.loadFromFile("Resource Files/Menus/quit.png")) //try to load the texture. if its wrong, give error
		textQuit.loadFromFile("error.jpg");

	if (!textHighlightResume.loadFromFile("Resource Files/Menus/Resume_Highlight.png")) //try to load the texture. if its wrong, give error
		textHighlightResume.loadFromFile("error.jpg");
	if (!textHighlightOption.loadFromFile("Resource Files/Menus/Options_Highlight.png")) //try to load the texture. if its wrong, give error
		textHighlightOption.loadFromFile("error.jpg");
	if (!textHighlightQuit.loadFromFile("Resource Files/Menus/Quit_Highlight.png")) //try to load the texture. if its wrong, give error
		textHighlightQuit.loadFromFile("error.jpg");

	spriteResume.setTexture(textResume);
	spriteOption.setTexture(textOption);
	spriteQuit.setTexture(textQuit);

	bg01.setTexture(textBg01);
	
}

void inGameMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void inGameMenu::moveUp()
{

}

void inGameMenu::moveDown()
{

}

int inGameMenu::checkState() {
	return mState;
}

void inGameMenu::scale(sf::RenderWindow &window) {

	mState = 2;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	spriteResume.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteOption.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteQuit.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(643 * bg01.getScale().x, 546 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(643 * bg01.getScale().x, 725 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(643 * bg01.getScale().x, 896 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));

	spriteResume.setPosition(700 * bg01.getScale().x, 550 * bg01.getScale().y);
	spriteOption.setPosition(700 * bg01.getScale().x, 730 * bg01.getScale().y);
	spriteQuit.setPosition(700 * bg01.getScale().x, 900 * bg01.getScale().y);

}
