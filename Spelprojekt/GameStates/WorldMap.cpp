#include "WorldMap.h"

WorldMap::WorldMap(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	mTimer = 0;
	mState = 7;
	setFonts();
	setTextures();
	
	mRects[0] = new sf::IntRect(sf::Vector2i(940, 280), sf::Vector2i(75, 25));
	mRects[1] = new sf::IntRect(sf::Vector2i(980, 380), sf::Vector2i(75, 25));
	mRects[2] = new sf::IntRect(sf::Vector2i(1700, 480), sf::Vector2i(145, 25));
	mRects[3] = new sf::IntRect(sf::Vector2i(1890, 840), sf::Vector2i(145, 30));
	mRects[4] = new sf::IntRect(sf::Vector2i(9900, 535), sf::Vector2i(75, 25));
	mRects[5] = new sf::IntRect(sf::Vector2i(1020, 180), sf::Vector2i(95, 25));
	//Test
}

WorldMap::WorldMap()
{

}

WorldMap::~WorldMap()
{
	delete 	highlightTexture01;
	delete texture01;

	delete 	bg01;
	delete highlightSprite01;
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

	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		std::cout << "It's in!" << std::endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 2;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		std::cout << "It's in!" << std::endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 3;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}

	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		std::cout << "It's in!" << std::endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 4;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}
			
	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		std::cout << "It's in!" << std::endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//mState = 8;
			mRegion = 5;
			std::cout << "mRegion is now " << mRegion << std::endl;
			reset = true;
		}
	}

	if (mRects[5]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mState = 3;
			//window.close();
			reset = true;
		}
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
*/
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		std::cout << "Inside" << " ";
		//window.close();
	}
	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		std::cout << "dasda";*/

	/*
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
	*/
/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		WorldMap::moveUp();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mUp)
	{
		mUp = false;
	}*/

/*
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
		if (selectedIndex == 5) {
			window.close();
		}
	}
*/
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void WorldMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(*bg01);
	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
	window.draw(menu[i]);
	}
	*/
}

void WorldMap::setTextures()
{

	if (!texture01->loadFromFile("Resource Files/Backgrounds/World_Map_pins.png")) //try to load the texture. if its wrong, give error
		texture01->loadFromFile("error.jpg");

	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	bg01->setTexture(*texture01);
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

}

void WorldMap::moveDown()
{

}

int WorldMap::checkState(){
	return mState;
}

void WorldMap::scale(sf::RenderWindow &window) {

	mState = 7;
	mRegion = 0;

	bg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(940 * bg01->getScale().x, 280 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(980 * bg01->getScale().x, 380 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(18900 * bg01->getScale().x, 840 * bg01->getScale().y), sf::Vector2i(145 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[3] = new sf::IntRect(sf::Vector2i(1700 * bg01->getScale().x, 480 * bg01->getScale().y), sf::Vector2i(145 * bg01->getScale().x, 30 * bg01->getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(1890 * bg01->getScale().x, 840 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[5] = new sf::IntRect(sf::Vector2i(1020 * bg01->getScale().x, 180 * bg01->getScale().y), sf::Vector2i(95 * bg01->getScale().x, 25 * bg01->getScale().y));

}

int WorldMap::getRegion() {
	return mRegion;
}

void WorldMap::resetRegion() {
	mRegion = 0;
}