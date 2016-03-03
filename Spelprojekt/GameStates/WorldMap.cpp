#include "WorldMap.h"

WorldMap::WorldMap(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 7;
	setFonts();
	setTextures();
	
	mRects[0] = new sf::IntRect(sf::Vector2i(900, 335), sf::Vector2i(75, 25));
	mRects[1] = new sf::IntRect(sf::Vector2i(1170, 290), sf::Vector2i(75, 25));
	mRects[2] = new sf::IntRect(sf::Vector2i(1635, 780), sf::Vector2i(95, 25));
	//Test
}

WorldMap::WorldMap()
{

}

WorldMap::~WorldMap()
{

}

void WorldMap::updateWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	//std::cout << window.getSize().x << " " << window.getSize().y << " " << mEvent.size.width << " " << mEvent.size.height << std::endl;
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/

	std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": WorldMap :" << highlightSprite01.getPosition().y << std::endl;


	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 1;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}
	else
		//set sprite to regular texture

	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 2;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}
	else
		//set sprite to regular texture

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			window.close();
			reset = true;
		}
	}
	else
		//set sprite to regular texture

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		std::cout << "Inside" << " ";
		//window.close();
	}
	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		std::cout << "dasda";*/


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		//WorldMap::moveDown();

		//(sf::Vector2i(900, 335), sf::Vector2i(75, 25));
		//sf::Vector2i(1635, 780), sf::Vector2i(95, 25)
		mRects[0] = new sf::IntRect(sf::Vector2i(900 * bg01.getScale().x, 335 * bg01.getScale().y), sf::Vector2i(75 * bg01.getScale().x, 25 * bg01.getScale().y));
		mRects[1] = new sf::IntRect(sf::Vector2i(1170 * bg01.getScale().x, 290 * bg01.getScale().y), sf::Vector2i(75 * bg01.getScale().x, 25 * bg01.getScale().y));
		mRects[2] = new sf::IntRect(sf::Vector2i(1635 * bg01.getScale().x, 780 * bg01.getScale().y), sf::Vector2i(95 * bg01.getScale().x, 25 * bg01.getScale().y));

	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		WorldMap::moveUp();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mUp)
	{
		mUp = false;
	}*/


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mReturn)
	{
		mReturn = false;
		if (selectedIndex == 0) {
			//mState = 8;
			mRegion = 1;
		}
		if (selectedIndex == 1) {
			//mState = 8;
			mRegion = 2;
		}
		if (selectedIndex == 2) {
			window.close();
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void WorldMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
	window.draw(menu[i]);
	}
	*/
}

void WorldMap::setTextures()
{

	if (!texture01.loadFromFile("Resource Files/Backgrounds/worldMap_temp.jpg")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	//highlightSprite01.setTexture(highlightTexture01);


}

void WorldMap::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void WorldMap::moveUp()
{
	/*if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}*/
}

void WorldMap::moveDown()
{
	/*if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}*/

}

int WorldMap::checkState(){
	return mState;
}

void WorldMap::scale(sf::RenderWindow &window) {

	mState = 7;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(900 * bg01.getScale().x, 335 * bg01.getScale().y), sf::Vector2i(75 * bg01.getScale().x, 25 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(650 * bg01.getScale().x, 740 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1635 * bg01.getScale().x, 780 * bg01.getScale().y), sf::Vector2i(95 * bg01.getScale().x, 25 * bg01.getScale().y));

}

int WorldMap::getRegion() {
	return mRegion;
}

void WorldMap::resetRegion() {
	mRegion = 0;
}