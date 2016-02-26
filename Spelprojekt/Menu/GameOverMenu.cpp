#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	bg01.scale(33, 33);
	mTimer = 0;
	mState = 2;
	setFonts();
	setTextures();
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	gameOver.setFont(font);
	gameOver.setColor(sf::Color::Cyan);
	gameOver.setString("GAME OVER");
	gameOver.setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	selectedIndex = 0;
	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));

}

GameOverMenu::~GameOverMenu()
{
}

void GameOverMenu::updateGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
		mClick = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		GameOverMenu::moveDown();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		GameOverMenu::moveUp();
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
			mState = 3;
		}
		if (selectedIndex == 1) {
			window.close();
		}
	}
}

void GameOverMenu::displayMenu01(sf::RenderWindow &window)
{

	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(gameOver);
	// draw background window.draw(bg01);
	//	std::cout << highlightSprite01.getPosition().x << ": GameOverMenu :" << highlightSprite01.getPosition().y << std::endl;
	/*
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mMouse.x > 10 && mMouse.x < 200 && mMouse.y > 235 && mMouse.y < 365) // left click if its on the option
	{
	window.close();
	}
	if (mMouse.x > highlightSprite01.getPosition().x * highlightSprite01.getScale().x && mMouse.x < highlightSprite01.getPosition().y - 35 && mMouse.y > highlightSprite01.getPosition().y && mMouse.y < highlightSprite01.getPosition().y + 30)
	{
	highlightSprite01.setPosition(10, 235);
	window.draw(highlightSprite01);
	}
	*/

}

void GameOverMenu::setTextures()
{
	
	if (!textBg01.loadFromFile("Resource Files/Menus/Decline.png")) //try to load the texture. if its wrong, give error
		textBg01.loadFromFile("error.jpg");

	if (!highlighttextBg01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	highlighttextBg01.loadFromFile("error.jpg");

	bg01.setTexture(textBg01);
	highlightSprite01.setTexture(highlighttextBg01);
	
}

void GameOverMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void GameOverMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void GameOverMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}

int GameOverMenu::checkState()
{
	//std::cout << mState << std::endl;
	int i = mState;
	mState = 2;
	return i;
}

/* Not usefull at the moment
void GameOverMenu::getTurns(int turns)
{
mTurns = turns;
}

int GameOverMenu::setTurns()
{
return mTurns;
}
*/