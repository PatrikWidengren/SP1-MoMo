#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	bg01->scale(33, 33);
	mTimer = 0;
	mState = 5;
	setFonts();
	setTextures();

	gameOver.setFont(font);
	gameOver.setColor(sf::Color::Cyan);
	gameOver.setString("GAME OVER");
	gameOver.setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	selectedIndex = 0;

	//mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	//mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));

}

GameOverMenu::~GameOverMenu()
{

	delete highlighttextBg01;
	delete textBg01;

	delete bg01;
	delete highlightSprite01;
}

void GameOverMenu::updateGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
		mClick = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
		mState = 3;
	}

}

void GameOverMenu::displayMenu01(sf::RenderWindow &window)
{

	sf::RectangleShape blackness(sf::Vector2f(window.getSize().x, window.getSize().y));
	blackness.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(blackness);
	window.draw(*bg01);
	window.draw(gameOver);

}

void GameOverMenu::setTextures()
{
	
	if (!textBg01->loadFromFile("Resource Files/Menus/Decline.png")) //try to load the texture. if its wrong, give error
		textBg01->loadFromFile("error.jpg");

	bg01->setTexture(*textBg01);	
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

}

void GameOverMenu::moveDown()
{

}

int GameOverMenu::checkState() {
	return mState;
}

void GameOverMenu::scale(sf::RenderWindow &window) {

	mState = 5;
	
	bg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	
	mRects[0] = new sf::IntRect(sf::Vector2i(643 * bg01->getScale().x, 546 * bg01->getScale().y), sf::Vector2i(550 * bg01->getScale().x, 100 * bg01->getScale().y));


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