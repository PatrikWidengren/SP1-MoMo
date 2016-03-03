#include "startMenu.h"

startMenu::startMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 3;
	setFonts();
	setTextures();

	spriteContinue.setPosition(689, 525);
	spriteNewgame.setPosition(689, 635);
	spriteOption.setPosition(689, 755);
	spriteCredits.setPosition(689, 875);
	spriteExit.setPosition(1770, 45);

	/*
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 1));


	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit to Desktop");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 3));
	*/
	selectedIndex = 0;

	mRects[3] = new sf::IntRect(sf::Vector2i(640, 510), sf::Vector2i(540, 100));
	mRects[0] = new sf::IntRect(sf::Vector2i(640, 630), sf::Vector2i(540, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(650, 750), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(1750, 35), sf::Vector2i(115, 95));
	mRects[4] = new sf::IntRect(sf::Vector2i(650, 870), sf::Vector2i(550, 100));


}

startMenu::startMenu()
{

}

startMenu::~startMenu()
{

}

void startMenu::updateStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	//std::cout << window.getSize().x << " " << window.getSize().y << " " << mEvent.size.width << " " << mEvent.size.height << std::endl;
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	std::cout << mMouse.x << " "<< mState << " " << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": StartMenu :" << highlightSprite01.getPosition().y << std::endl;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteNewgame.setTexture(textHighlightNewgame);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
			mClick = false;
			mState = 7;
		}
	}
	else
		spriteNewgame.setTexture(textNewgame);

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
		spriteExit.setTexture(textHighlightExit);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			window.close();
		}
	}
	else
		spriteExit.setTexture(textExit);

	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteContinue.setTexture(textHighlightContinue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 1; Continue
		}
	}
	else
		spriteContinue.setTexture(textContinue);

	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteCredits.setTexture(textHighlightCredits);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 1; Credits
		}
	}
	else
		spriteCredits.setTexture(textCredits);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y))) {
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		startMenu::moveDown();

	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		startMenu::moveUp();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mUp)
	{
		mUp = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mReturn)
	{
		mReturn = false;
		if (selectedIndex == 0) {
			reset = true;
			mState = 1;
		}
		if (selectedIndex == 1) {
			mState = 4;
		}
		if (selectedIndex == 2) {
			window.close();
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void startMenu::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	window.draw(spriteContinue);
	window.draw(spriteNewgame);
	window.draw(spriteOption);
	window.draw(spriteCredits);
	window.draw(spriteExit);


	/*
	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}
	*/
}

void startMenu::setTextures()
{

	if (!textBg01.loadFromFile("Resource Files/Backgrounds/Background_StartMenu.png")) //try to load the texture. if its wrong, give error
		textBg01.loadFromFile("error.jpg");

	if (!textContinue.loadFromFile("Resource Files/Menus/Decline.png"))
		textContinue.loadFromFile("error.jpg");
	if (!textNewgame.loadFromFile("Resource Files/Menus/NewGame.png"))
		textNewgame.loadFromFile("error.jpg");
	if (!textOption.loadFromFile("Resource Files/Menus/Options.png"))
		textOption.loadFromFile("error.jpg");
	if (!textCredits.loadFromFile("Resource Files/Menus/Credits.png"))
		textCredits.loadFromFile("error.jpg");
	if (!textExit.loadFromFile("Resource Files/Menus/Decline.png"))
		textExit.loadFromFile("error.jpg");

	if (!textHighlightContinue.loadFromFile("Resource Files/Menus/Decline_Highlight.png"))
		textHighlightContinue.loadFromFile("error.jpg");
	if (!textHighlightNewgame.loadFromFile("Resource Files/Menus/NewGame_Highlight.png"))
		textHighlightNewgame.loadFromFile("error.jpg");
	if (!textHighlightOption.loadFromFile("Resource Files/Menus/Options_Highlight.png"))
		textHighlightOption.loadFromFile("error.jpg");
	if (!textHighlightCredits.loadFromFile("Resource Files/Menus/Credits_Highlight.png"))
		textHighlightCredits.loadFromFile("error.jpg");
	if (!textHighlightExit.loadFromFile("Resource Files/Menus/Decline_Highlight.png"))
		textHighlightExit.loadFromFile("error.jpg");

	bg01.setTexture(textBg01);

	spriteContinue.setTexture(textContinue);
	spriteNewgame.setTexture(textNewgame);
	spriteOption.setTexture(textOption);
	spriteCredits.setTexture(textCredits);
	spriteExit.setTexture(textExit);
}

void startMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void startMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void startMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}

int startMenu::checkState(){
	return mState;
}

void startMenu::scale(sf::RenderWindow &window) {

	mState = 3;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	spriteContinue.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteNewgame.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteOption.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteExit.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteCredits.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[3] = new sf::IntRect(sf::Vector2i(640 * bg01.getScale().x, 510 * bg01.getScale().y), sf::Vector2i(540 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[0] = new sf::IntRect(sf::Vector2i(640 * bg01.getScale().x, 630 * bg01.getScale().y), sf::Vector2i(540 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(650 * bg01.getScale().x, 750 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1750 * bg01.getScale().x, 35 * bg01.getScale().y), sf::Vector2i(115 * bg01.getScale().x, 95 * bg01.getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(650 * bg01.getScale().x, 870 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));

	spriteContinue.setPosition(689 * bg01.getScale().x, 525 * bg01.getScale().y);
	spriteNewgame.setPosition(689 * bg01.getScale().x, 635 * bg01.getScale().y);
	spriteOption.setPosition(689 * bg01.getScale().x, 755 * bg01.getScale().y);
	spriteExit.setPosition(1770 * bg01.getScale().x, 45 * bg01.getScale().y);
	spriteCredits.setPosition(689 * bg01.getScale().x, 875 * bg01.getScale().y);
}
