#include "WorldMap.h"

WorldMap::WorldMap(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	mTimer = 0;
	mState = 7;
	setFonts();
	setTextures();
	int g = 0; int h = 0; int j = 0; int k = 0;

	mMapRegions[0].unlock = false; mMapRegions[1].unlock = false; mMapRegions[2].unlock = false; mMapRegions[3].unlock = false;
	mMapRegions[0].mCostRegion = 30; mMapRegions[1].mCostRegion = 300; mMapRegions[2].mCostRegion = 3000; mMapRegions[3].mCostRegion = 6000;


	mRects[0] = new sf::IntRect(sf::Vector2i(940, 280), sf::Vector2i(75, 25));
	mRects[1] = new sf::IntRect(sf::Vector2i(980, 380), sf::Vector2i(75, 25));
	mRects[2] = new sf::IntRect(sf::Vector2i(1700, 480), sf::Vector2i(145, 25));
	mRects[3] = new sf::IntRect(sf::Vector2i(1890, 840), sf::Vector2i(145, 30));
	mRects[4] = new sf::IntRect(sf::Vector2i(9900, 535), sf::Vector2i(75, 25));
	mRects[5] = new sf::IntRect(sf::Vector2i(1020, 180), sf::Vector2i(95, 25));
	//Test
	mDemDupies = 100;

	spriteGreenDot01->setColor(sf::Color(0, 0, 0, 0));
	spriteGreenDot02->setColor(sf::Color(0, 0, 0, 0));
	spriteGreenDot03->setColor(sf::Color(0, 0, 0, 0));
	spriteGreenDot04->setColor(sf::Color(0, 0, 0, 0));


	setFonts();
}

WorldMap::WorldMap()
{

}

WorldMap::~WorldMap()
{
	delete 	highlightTexture01;
	delete texture01;
	delete textGreenDot;

	delete spriteGreenDot01;
	delete spriteGreenDot02;
	delete spriteGreenDot03;
	delete spriteGreenDot04;

	delete 	bg01;
	delete highlightSprite01;
}

void WorldMap::updateWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse)
{

	//std::cout << window.getSize().x << " " << window.getSize().y << " " << mEvent.size.width << " " << mEvent.size.height << std::endl;
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	mShowDemDupies.setString(WriteDopies(mDemDupies));

	mMapRegions[0].mapRegionText.setString(WriteRegionCost(mMapRegions[0].mCostRegion)); mMapRegions[1].mapRegionText.setString(WriteRegionCost(mMapRegions[1].mCostRegion)); mMapRegions[2].mapRegionText.setString(WriteRegionCost(mMapRegions[2].mCostRegion)); mMapRegions[3].mapRegionText.setString(WriteRegionCost(mMapRegions[3].mCostRegion));

	//int mCostRegion0; int mCostRegion1; int mCostRegion2; int mCostRegion3;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/
	std::cout << mMouse.x << "  " << mMouse.y << std::endl;
	if (mMouse.x > 1819 && mMouse.y > 1016)
	{
			mDemDupies+= 1000; std::cout << "DUPIES: " << mDemDupies << std::endl;

	}

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (mMapRegions[0].unlock == false)
		{
			fadeText(mMapRegions[0].RegionID);
			mMapRegions[0].mapRegionText.setColor(sf::Color(255, 255, 255, g));
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			if (mMapRegions[0].unlock == true)
			{
				mClick = false;
				//mState = 8;
				mRegion = 1;
				std::cout << "Dupies left: " << mDemDupies << std::endl;
				reset = true;
			}
			if (!mMapRegions[0].unlock && mDemDupies > 30)
			{
				spriteGreenDot01->setColor(sf::Color(255, 255, 255, 255));
				mDemDupies -= 30;
				mMapRegions[0].unlock = true;
				mMapRegions[0].mapRegionText.move(10000, 0);
			}
		}
	}
	else
	{
		if (g >= 10)
		{
			g -= 10;
			mMapRegions[0].mapRegionText.setColor(sf::Color(255, 255, 255, g));
		}
	}


	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (mMapRegions[1].unlock == false)
			fadeText(mMapRegions[1].RegionID);	mMapRegions[1].mapRegionText.setColor(sf::Color(255, 255, 255, h));


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			if (mMapRegions[1].unlock == true)
			{
				mClick = false;
				//mState = 8;
				mRegion = 2;
				std::cout << "Dupies left: " << mDemDupies << std::endl;
				reset = true;
			}
			if (!mMapRegions[1].unlock && mDemDupies > 300)
			{
				spriteGreenDot02->setColor(sf::Color(255, 255, 255, 255));
				mDemDupies -= 300;
				mMapRegions[1].unlock = true;
				mMapRegions[1].mapRegionText.move(10000, 0);
			}
		}
	}
	else
	{
		if (h >= 10)
		{
			h -= 10;
			mMapRegions[1].mapRegionText.setColor(sf::Color(255, 255, 255, h));
		}
	}

	

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
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
		if (mMapRegions[2].unlock == false)
			fadeText(mMapRegions[2].RegionID); mMapRegions[2].mapRegionText.setColor(sf::Color(255, 255, 255, j));


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			if (mMapRegions[2].unlock == true)
			{
				std::cout << "Dupies left: " << mDemDupies << std::endl;
				mClick = false;
				//mState = 8;
				mRegion = 4;
				reset = true;
			}
			if (!mMapRegions[2].unlock && mDemDupies > 3000)
			{
				spriteGreenDot03->setColor(sf::Color(255, 255, 255, 255));
				mDemDupies -= 3000;
				mMapRegions[2].unlock = true;
				mMapRegions[2].mapRegionText.move(10000, 0);
			}
		}
	}
	else
	{
		if (j >= 10)
		{
			j -= 10;
			mMapRegions[2].mapRegionText.setColor(sf::Color(255, 255, 255, j));
		}
	}
			
	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if(mMapRegions[3].unlock == false)
		fadeText(mMapRegions[3].RegionID); mMapRegions[3].mapRegionText.setColor(sf::Color(255, 255, 255, k));


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			if (mMapRegions[3].unlock == true)
			{
				std::cout << "Dupies left: " << mDemDupies << std::endl;
				mClick = false;
				//mState = 8;
				mRegion = 5;
				reset = true;
			}
			if (!mMapRegions[3].unlock && mDemDupies > 6000)
			{
				spriteGreenDot04->setColor(sf::Color(255, 255, 255, 255));
				mDemDupies -= 6000;
				mMapRegions[3].unlock = true;
				mMapRegions[3].mapRegionText.move(10000, 0);
			}
		}
	}
	else
	{
		if (k >= 10)
		{
			k -= 10;
			mMapRegions[3].mapRegionText.setColor(sf::Color(255, 255, 255, k));

		}
	}

	if (mRects[5]->contains(sf::Vector2i(mMouse.x, mMouse.y))) //NOT A REGION NOT A REGION NOT A REGION NOT A REGION NOT A REGION 
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

	if (mShowDemDupies.getPosition().x < -420)
	{
		mShowDemDupies.setPosition( 3000, mShowDemDupies.getPosition().y);
	}
	mShowDemDupies.move(-4, 0);



}

void WorldMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(*bg01);
	window.draw(*spriteGreenDot01);
	window.draw(*spriteGreenDot02);
	window.draw(*spriteGreenDot03);
	window.draw(*spriteGreenDot04);

	window.draw(mMapRegions[0].mapRegionText);
	window.draw(mMapRegions[1].mapRegionText);
	window.draw(mMapRegions[2].mapRegionText);
	window.draw(mMapRegions[3].mapRegionText);

	window.draw(mShowDemDupies);

}

void WorldMap::setTextures()
{

	if (!texture01->loadFromFile("Resource Files/Backgrounds/World_Map_pins.png")) //try to load the texture. if its wrong, give error
		texture01->loadFromFile("error.jpg");

	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");
	if (!textGreenDot->loadFromFile("Resource Files/Sprites/Knapp-on.png")) //try to load the texture. if its wrong, give error
		textGreenDot->loadFromFile("Resource Files/error.jpg");

	spriteGreenDot01->setTexture(*textGreenDot);
	spriteGreenDot02->setTexture(*textGreenDot);
	spriteGreenDot03->setTexture(*textGreenDot);
	spriteGreenDot04->setTexture(*textGreenDot);

	bg01->setTexture(*texture01);
	//highlightSprite01.setTexture(highlightTexture01);

}

void WorldMap::setFonts()
{

	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
	mMapRegions[0].mapRegionText.setFont(font);	mMapRegions[1].mapRegionText.setFont(font);	mMapRegions[2].mapRegionText.setFont(font);	mMapRegions[3].mapRegionText.setFont(font);
	mMapRegions[0].mapRegionText.setCharacterSize(30); 	mMapRegions[1].mapRegionText.setCharacterSize(30);	mMapRegions[2].mapRegionText.setCharacterSize(30);	mMapRegions[3].mapRegionText.setCharacterSize(30);
	mMapRegions[0].RegionID = "0"; mMapRegions[1].RegionID = "1"; mMapRegions[2].RegionID = "2"; mMapRegions[3].RegionID = "3";
	mMapRegions[0].mapRegionText.setColor(sf::Color(255, 255, 255, 0)); mMapRegions[1].mapRegionText.setColor(sf::Color(255, 255, 255, 0)); mMapRegions[2].mapRegionText.setColor(sf::Color(255, 255, 255, 0)); mMapRegions[3].mapRegionText.setColor(sf::Color(255, 255, 255, 0));

	mShowDemDupies.setFont(font);
	mShowDemDupies.setCharacterSize(40);
	mShowDemDupies.setColor(sf::Color().White);
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

	spriteGreenDot01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGreenDot02->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGreenDot03->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGreenDot04->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(930 * bg01->getScale().x, 270	 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(980 * bg01->getScale().x, 380 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(18900 * bg01->getScale().x, 840 * bg01->getScale().y), sf::Vector2i(145 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[3] = new sf::IntRect(sf::Vector2i(1705 * bg01->getScale().x, 480 * bg01->getScale().y), sf::Vector2i(145 * bg01->getScale().x, 30 * bg01->getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(1890 * bg01->getScale().x, 830 * bg01->getScale().y), sf::Vector2i(75 * bg01->getScale().x, 25 * bg01->getScale().y));
	mRects[5] = new sf::IntRect(sf::Vector2i(1020 * bg01->getScale().x, 180 * bg01->getScale().y), sf::Vector2i(95 * bg01->getScale().x, 25 * bg01->getScale().y));

	mShowDemDupies.setPosition(1700 * bg01->getScale().x, 15 * bg01->getScale().y);

	spriteGreenDot01->setPosition(933 * bg01->getScale().x, 273* bg01->getScale().y);
	spriteGreenDot02->setPosition(978 * bg01->getScale().x, 373 * bg01->getScale().y);
	spriteGreenDot03->setPosition(1697 * bg01->getScale().x, 475 * bg01->getScale().y);
	spriteGreenDot04->setPosition(1883 * bg01->getScale().x, 828 * bg01->getScale().y);

	mMapRegions[0].mapRegionText.setPosition(933 * bg01->getScale().x, 223 * bg01->getScale().y);
	mMapRegions[1].mapRegionText.setPosition(978 * bg01->getScale().x, 323 * bg01->getScale().y);
	mMapRegions[2].mapRegionText.setPosition(1107 * bg01->getScale().x, 425 * bg01->getScale().y);
	mMapRegions[3].mapRegionText.setPosition(1183 * bg01->getScale().x, 788 * bg01->getScale().y);
	
	if(mMapRegions[0].unlock == true)
	mMapRegions[0].mapRegionText.move(10000, 0);

	if (mMapRegions[1].unlock == true)
		mMapRegions[1].mapRegionText.move(10000, 0);


	if (mMapRegions[2].unlock == true)
		mMapRegions[2].mapRegionText.move(10000, 0);


	if (mMapRegions[3].unlock == true)
		mMapRegions[3].mapRegionText.move(10000, 0);

}

int WorldMap::getRegion() {
	return mRegion;
}

void WorldMap::resetRegion() {
	mRegion = 0;
}

void WorldMap::setDemDopies(int demDopies)
{
	mDemDupies = demDopies;
}

void WorldMap::addDemDopies(int demDopies)
{
	mDemDupies += demDopies;
}

int WorldMap::getDemDopies()
{
	return mDemDupies;
}

std::string WorldMap::WriteDopies(int demDopies) 
{
	std::ostringstream o;
	o << "You got: " << demDopies << " Dopies!";
	return o.str();
}

std::string WorldMap::WriteRegionCost(int cost)
{
	int e = 0;
	std::ostringstream o;
	if (getDemDopies() < cost)
	{
		e = cost - getDemDopies();

		o << "This Region Cost: " << cost << ". You Need " << e << " Dopies More!";

	}
	else 
		o << "This Region Cost: " << cost << ". Do you want to buy it?";

	return o.str();
}


void WorldMap::fadeText(std::string id)
{
	if (id == "0")
	g = 255;
	if (id == "1")
	h = 255;
	if (id == "2")
	j = 255;
	if (id == "3")
	k = 255;

}