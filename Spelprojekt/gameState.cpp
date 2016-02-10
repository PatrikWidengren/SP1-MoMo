#include "gameState.h"
gameState::gameState(sf::RenderWindow &window)
{
	mState = 1;
	mInGameMenu01 = new inGameMenu(window.getSize().x, window.getSize().y);
	mStartMenu01 = new startMenu(window.getSize().x, window.getSize().y);
	mOptionMenu01 = new optionMenu(window.getSize().x, window.getSize().y);
}

gameState::~gameState()
{
}

void gameState::drawInGameMenu(sf::RenderWindow &window, sf::Vector2i mouse)
{
	
	mInGameMenu01->updateInGameMenu(window);
	mInGameMenu01->displayMenu01(window);
	
}

void gameState::drawStartMenu(sf::RenderWindow &window, sf::Vector2i mouse)
{
	mStartMenu01->updateStartMenu(window);
	mStartMenu01->displayMenu01(window);
	
}

void gameState::drawInGame(sf::RenderWindow &window, sf::Vector2i mouse)
{

}

void gameState::drawOptionMenu(sf::RenderWindow &window, sf::Vector2i mouse)
{
	mOptionMenu01->updateoptionMenu(window);
	mOptionMenu01->displayMenu01(window);
}

void gameState::gameStatesHandler(sf::RenderWindow &window, sf::Vector2i mouse)
{
	switch (mState) //switch that hold the states of the game
	{
	case 1: //Game state 1. in game. 
		drawInGame(window, mouse);
		break;

	case 2: //Case 2, Draw ingame menu
		drawInGameMenu(window, mouse);
		break;

	case 3: //State 3. Start menu.
		drawStartMenu(window, mouse);
		break;

	case 4: //state 4. option.

		break;

	default:
		std::cout << "default gamestate";
		break;
	}

	//Outside the gamestates, check if the user changes the gamestate.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		mState = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mState = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mState = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		mState = 4;
	}

}
