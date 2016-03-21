#include "RegionMap.h"
#include <sstream>

RegionMap::RegionMap(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	mTimer = 0;
	mState = 7;
	selectedMow = 0;
	selectedHedgeCutter = 0;
	mInternalState = 0;
	mRegionState = 0;

	mRegions[1].BackgroundName = "Resource Files/Backgrounds/Garden_01.png";
	mRegions[1].levelCount = 5;

	mRegions[2].BackgroundName = "Resource Files/Backgrounds/Garden_02.png";
	mRegions[2].levelCount = 5;

	mRegions[3].BackgroundName = "Resource Files/Backgrounds/Garden_03.png";
	mRegions[3].levelCount = 5;

	mRegions[4].BackgroundName = "Resource Files/Backgrounds/Garden_04.png";
	mRegions[4].levelCount = 5;

	mRegions[5].BackgroundName = "Resource Files/Backgrounds/Garden_05.png";
	mRegions[5].levelCount = 8;

	setFonts();
	setTextures();

	spriteShop->setPosition(582, 1080);
	spriteArrow01->setPosition(950, 730);
	spriteArrow01->setScale(-1, 1);
	spriteArrow02->setPosition(1343, 730);
	spriteArrow03->setPosition(950, 900);
	spriteArrow03->setScale(-1, 1);
	spriteArrow04->setPosition(1343, 900);

	spriteHedgecutter->setPosition(650 + 582, 700);
	
	spriteGrassMowerDescription->setPosition(400 + 682, 650);
	spriteGrassMower->setPosition(160 + 582, 700);

	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));

	mRects[3] = new sf::IntRect(sf::Vector2i(3 + 582, 850), sf::Vector2i(116, 173));
	mRects[4] = new sf::IntRect(sf::Vector2i(285 + 582, 850), sf::Vector2i(116, 180));
	mRects[5] = new sf::IntRect(sf::Vector2i(493 + 582, 850), sf::Vector2i(116, 173));
	mRects[6] = new sf::IntRect(sf::Vector2i(775 + 582, 850), sf::Vector2i(116, 180));

}

RegionMap::RegionMap()
{

}

RegionMap::~RegionMap()
{
	delete textureShop;
	delete textArrow01;
	delete textHighlightArrow01;

	delete spriteGrassMower;
	delete spriteGrassMowerDescription;
	delete spriteHedgecutter;

	delete spriteArrow01;
	delete spriteArrow02;
	delete spriteArrow03;
	delete spriteArrow04;

	delete spriteShop;
	delete spriteLevels;
	delete bg01;
}

void RegionMap::updateRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	switch (mInternalState) {
	case 0: //nothing visible, yet

		//if (spriteShop->getPosition().y >= 1080 * bg01->getScale().y)

		spriteShop->setPosition(582 * bg01->getScale().x, 1080 * bg01->getScale().y);

		spriteArrow01->setPosition(950 * bg01->getScale().x, 1120 * bg01->getScale().y);
		spriteArrow02->setPosition(1343 * bg01->getScale().x, 1120 * bg01->getScale().y);
		spriteArrow03->setPosition(950 * bg01->getScale().x, 1513 * bg01->getScale().y);
		spriteArrow04->setPosition(1343 * bg01->getScale().x, 1513 * bg01->getScale().y);

		spriteGrassMowerDescription->setPosition(1450 * bg01->getScale().x, 1140 * bg01->getScale().y);
		spriteGrassMower->setPosition(960 * bg01->getScale().x, 1140 * bg01->getScale().y);
		spriteHedgecutter->setPosition(960 * bg01->getScale().x, 1140 * bg01->getScale().y);
		
		mRects[3] = new sf::IntRect(sf::Vector2i(3 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(285 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(493 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));

		break;

	case 1: //Level select visible

		if (spriteShop->getPosition().y < window.getSize().y)
		{
			spriteShop->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteArrow01->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteArrow02->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteArrow03->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteArrow04->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);

			spriteGrassMowerDescription->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteGrassMower->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);
			spriteHedgecutter->move(0 * bg01->getScale().x, 4 * bg01->getScale().y);

			mRects[3] = new sf::IntRect(sf::Vector2i(3 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
			mRects[4] = new sf::IntRect(sf::Vector2i(287 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));
			mRects[7] = new sf::IntRect(sf::Vector2i(493 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
			mRects[6] = new sf::IntRect(sf::Vector2i(777 + 582 * bg01->getScale().x, 11200 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));

		}
		//levelRectReplacer_01
		if (mLevelRects != 0)
			delete[] mLevelRects;
		mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
		for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
			mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01->getScale().x, i * 100 * bg01->getScale().y), sf::Vector2i(200 * bg01->getScale().x, 100 * bg01->getScale().y));
		}

		//spriteShop->move(0 * bg01->getScale().x, 300 * bg01->getScale().y);
		break;


	case 2: //Shop visible

		std::cout << mMouse.x << mMouse.y << std::endl;

		if (spriteShop->getPosition().y >= window.getSize().y - spriteShop->getGlobalBounds().height)
		{
			spriteShop->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteArrow01->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteArrow02->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteArrow03->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteArrow04->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);

			spriteGrassMowerDescription->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteGrassMower->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);
			spriteHedgecutter->move(0 * bg01->getScale().x, -4 * bg01->getScale().y);



		}
		mRects[3] = new sf::IntRect(sf::Vector2i(880 * bg01->getScale().x, 730 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(1330  * bg01->getScale().x, 720 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(1330  * bg01->getScale().x, 720 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 + 582 * bg01->getScale().x, 830 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));


		break;
	}

	if (mInternalState == 1) {
		for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
			if (mLevelRects[i].contains(sf::Vector2i(mMouse.x, mMouse.y))) {
				std::cout << "It's inside " << i << "!" << std::endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
					mClick = false;
					mLevelToLoad = i + 1;
					mState = 8;
				}
			}
		}
	}

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mInternalState = 2;
			reset = true;
		}
	}

	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mInternalState = 1;
			reset = true;

			//levelRectReplacer_02 
			if (mLevelRects != 0)
				delete[] mLevelRects;
			mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
			for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
				mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01->getScale().x, i * 100 * bg01->getScale().y), sf::Vector2i(200 * bg01->getScale().x, 100 * bg01->getScale().y));
			}
		}
	}

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			if (mInternalState != 0) {
				mInternalState = 0;
			}
			else {
				mRegionState = 0;
			}

		}
		reset = true;

	}

	std::cout << "Mouse Coord: " << mMouse.x << " " << mMouse.y << std::endl;
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		std::cout << "Height: " << mLevelRects[i].height << " Width: " << mLevelRects[i].width << std::endl;
		std::cout << "Top: " << mLevelRects[i].top << " Left: " << mLevelRects[i].left << std::endl << std::endl;;
	}


#pragma region ArrowRects
	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow01->setTexture(*textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedMow >= 1)
			{
				selectedMow--;
			}
			spriteGrassMower->setTexture(textMowers[selectedMow]);
			spriteGrassMowerDescription->setTexture(textMowerDescription[selectedMow]);
		}
		else
			spriteArrow01->setTexture(*textArrow01);
	}

	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow02->setTexture(*textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedMow < 4)
			{
				selectedMow++;
			}
			spriteGrassMower->setTexture(textMowers[selectedMow]);	
			spriteGrassMowerDescription->setTexture(textMowerDescription[selectedMow]);
		}
		else
			spriteArrow02->setTexture(*textArrow01);
	}


	if (mRects[5]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow03->setTexture(*textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedHedgeCutter >= 1)
			{
				selectedHedgeCutter--;
			}
			spriteHedgecutter->setTexture(textHedgecutters[selectedHedgeCutter]);
		}
		else
			spriteArrow03->setTexture(*textArrow01);

	}


	if (mRects[6]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow04->setTexture(*textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedHedgeCutter < 1)
			{
				selectedHedgeCutter++;
			}
			spriteHedgecutter->setTexture(textHedgecutters[selectedHedgeCutter]);

		}
		else
			spriteArrow04->setTexture(*textArrow01);
	}


#pragma endregion



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
		{
			mDown = true;

			//RegionMap::moveDown();
			
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
		{
			mDown = false;
		}

		/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
		{
		mUp = true;
		RegionMap::moveUp();
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
				mState = 10;
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


void RegionMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(*bg01);
	window.draw(*spriteShop);
	window.draw(*spriteArrow01);
	window.draw(*spriteArrow02);
	window.draw(*spriteArrow03);
	window.draw(*spriteArrow04);
	window.draw(*spriteHedgecutter);
	window.draw(*spriteGrassMower);
	window.draw(*spriteGrassMowerDescription);
	if (mInternalState == 1) {
		for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
			window.draw(spriteLevels[i]);
		}
	}

	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
	window.draw(menu[i]);
	}
	*/
}

void RegionMap::setTextures()
{

	for (int i = 0; i < mMaxRegions; i++) {
		if (!textBackgrounds[i].loadFromFile(mRegions[i].BackgroundName)) //try to load the texture. if its wrong, give error
			textBackgrounds[i].loadFromFile("error.jpg");
	}

	if (!textLevels->loadFromFile("Resource Files/Menus/LevelPick.png"))
		textureShop->loadFromFile("error.jpg");

	if (!textureShop->loadFromFile("Resource Files/Menus/Shop_UI/Wood.png"))
		textureShop->loadFromFile("error.jpg");

	if (!textArrow01->loadFromFile("Resource Files/Menus/Arrow.png"))
		textArrow01->loadFromFile("error.jpg");

	if (!textHighlightArrow01->loadFromFile("Resource Files/Menus/Arrow_Click.png"))
		textHighlightArrow01->loadFromFile("error.jpg");
#pragma region Set Textures Mowers

	if (!textMowers[0].loadFromFile("Resource Files/Menus/Shop_UI/Mower_1_Big.png"))
		textMowers[0].loadFromFile("error.jpg");
	if (!textMowers[1].loadFromFile("Resource Files/Menus/Shop_UI/Mower_2_Big.png"))
		textMowers[1].loadFromFile("error.jpg");
	if (!textMowers[2].loadFromFile("Resource Files/Menus/Shop_UI/Mower_3_Big.png"))
		textMowers[2].loadFromFile("error.jpg");
	if (!textMowers[3].loadFromFile("Resource Files/Menus/Shop_UI/Mower_4_Big.png"))
		textMowers[3].loadFromFile("error.jpg");
	if (!textMowers[4].loadFromFile("Resource Files/Menus/Shop_UI/Mower_5_Big.png"))
		textMowers[4].loadFromFile("error.jpg");

	if (!textMowerDescription[0].loadFromFile("Resource Files/Sprites/Descriptions/lawnmower_0.png"))
		textMowerDescription[0].loadFromFile("error.jpg");
	if (!textMowerDescription[1].loadFromFile("Resource Files/Sprites/Descriptions/lawnmower_1.png"))
		textMowerDescription[1].loadFromFile("error.jpg");
	if (!textMowerDescription[2].loadFromFile("Resource Files/Sprites/Descriptions/lawnmower_2.png"))
		textMowerDescription[2].loadFromFile("error.jpg");
	if (!textMowerDescription[3].loadFromFile("Resource Files/Sprites/Descriptions/lawnmower_3.png"))
		textMowerDescription[3].loadFromFile("error.jpg");
	if (!textMowerDescription[4].loadFromFile("Resource Files/Sprites/Descriptions/lawnmower_4.png"))
		textMowerDescription[4].loadFromFile("error.jpg");

	if (!textHedgecutters[0].loadFromFile("Resource Files/Menus/Shop_UI/Hedgecutter_Small.png"))
		textHedgecutters[0].loadFromFile("error.jpg");
	if (!textHedgecutters[1].loadFromFile("Resource Files/Menus/Shop_UI/Hedgecutter_Big.png"))
		textHedgecutters[1].loadFromFile("error.jpg");

	spriteGrassMowerDescription->setTexture(textMowerDescription[0]);
	spriteGrassMower->setTexture(textMowers[0]);
	spriteHedgecutter->setTexture(textHedgecutters[0]);

#pragma endregion

	spriteArrow01->setTexture(*textArrow01);
	spriteArrow02->setTexture(*textArrow01);
	spriteArrow03->setTexture(*textArrow01);
	spriteArrow04->setTexture(*textArrow01);
	
	bg01->setTexture(textBackgrounds[mRegionState]);
	spriteShop->setTexture(*textureShop);


}

void RegionMap::setFonts()

{
	/*if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}*/
}

void RegionMap::moveUp()
{

}

void RegionMap::moveDown()
{

}

int RegionMap::checkState()
{
	return mState;
}

int RegionMap::checkRegionState() {
	return mRegionState;
}

void RegionMap::setRegionState(int state) {

	mRegionState = state;
	bg01->setTexture(textBackgrounds[mRegionState]);

	if (spriteLevels != 0)
	delete[] spriteLevels;
	spriteLevels = new sf::Sprite[mRegions[mRegionState].levelCount];
	mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
	
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01->getScale().x, i * 100 * bg01->getScale().y), sf::Vector2i(200 * bg01->getScale().x, 100 * bg01->getScale().y));
	}

	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		spriteLevels[i].setPosition(0 * bg01->getScale().x, i * 100 * bg01->getScale().y);
		spriteLevels[i].setScale(bg01->getScale().x, bg01->getScale().y);
		spriteLevels[i].setTexture(*textLevels);
	}
	//levelRectReplacer_03
	if (mLevelRects != 0)
		delete[] mLevelRects;
	mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01->getScale().x, i * 100 * bg01->getScale().y), sf::Vector2i(200 * bg01->getScale().x, 100 * bg01->getScale().y));
	}
}

std::string RegionMap::loadLevel() {
	std::stringstream ss;
	ss << "map" << "0" << mRegionState << "a" << "0" << mLevelToLoad << ".txt";
	std::string s;
	ss >> s;

	std::cout << s << std::endl;

	return s;
}

void RegionMap::scale(sf::RenderWindow &window) {

	mState = 7;
	mInternalState = 0;

	bg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	/*	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));
	*/

	spriteShop->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGrassMowerDescription->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteHedgecutter->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGrassMower->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow01->setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow02->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow03->setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow04->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		spriteLevels[i].setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	}



	mRects[0] = new sf::IntRect(sf::Vector2i(360 * bg01->getScale().x, 295 * bg01->getScale().y), sf::Vector2i(410 * bg01->getScale().x, 200 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(925 * bg01->getScale().x, 300 * bg01->getScale().y), sf::Vector2i(395 * bg01->getScale().x, 200 * bg01->getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660 * bg01->getScale().x, 75 * bg01->getScale().y), sf::Vector2i(180 * bg01->getScale().x, 145 * bg01->getScale().y));
	mRects[3] = new sf::IntRect(sf::Vector2i(950 * bg01->getScale().x, 730 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(285 + 582 * bg01->getScale().x, 850 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));
	mRects[5] = new sf::IntRect(sf::Vector2i(493 + 582 * bg01->getScale().x, 850 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 173 * bg01->getScale().y));
	mRects[6] = new sf::IntRect(sf::Vector2i(775 + 582 * bg01->getScale().x, 850 * bg01->getScale().y), sf::Vector2i(116 * bg01->getScale().x, 180 * bg01->getScale().y));
	
	if (mInternalState == 1) {
		spriteShop->setPosition(582 * bg01->getScale().x, 780 * bg01->getScale().y);
		spriteGrassMowerDescription->setPosition(400 + 682 * bg01->getScale().x,650 * bg01->getScale().y);
		spriteGrassMower->setPosition(130 + 582 * bg01->getScale().x, 450 * bg01->getScale().y);
		spriteArrow01->setPosition(950 * bg01->getScale().x, 500 * bg01->getScale().y);
		spriteArrow02->setPosition(245 + 582 * bg01->getScale().x, 500 * bg01->getScale().y);
		spriteArrow03->setPosition(410 + 582 * bg01->getScale().x, 500 * bg01->getScale().y);
		spriteArrow04->setPosition(555 + 582 * bg01->getScale().x, 500 * bg01->getScale().y);
	}
	else {
		spriteShop->setPosition(582 * bg01->getScale().x, 1080 * bg01->getScale().y);
		spriteGrassMowerDescription->setPosition(400 + 682 * bg01->getScale().x, 1050 * bg01->getScale().y);
		spriteGrassMower->setPosition(130 + 582 * bg01->getScale().x, 800 * bg01->getScale().y);
		spriteArrow01->setPosition(950 * bg01->getScale().x, 730 * bg01->getScale().y);
		spriteArrow02->setPosition(245 + 582 * bg01->getScale().x, 800 * bg01->getScale().y);
		spriteArrow03->setPosition(410 + 582 * bg01->getScale().x, 800 * bg01->getScale().y);
		spriteArrow04->setPosition(555 + 582 * bg01->getScale().x, 800 * bg01->getScale().y);
	}

	//levelRectReplacer_04
	if (mLevelRects != 0)
		delete[] mLevelRects;
	mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01->getScale().x, i * 100 * bg01->getScale().y), sf::Vector2i(200 * bg01->getScale().x, 100 * bg01->getScale().y));
	}

	if (spriteLevels != 0)
		delete[] spriteLevels;
	spriteLevels = new sf::Sprite[mRegions[mRegionState].levelCount];
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		spriteLevels[i].setPosition(0 * bg01->getScale().x, i * 100 * bg01->getScale().y);
		spriteLevels[i].setScale(bg01->getScale().x, bg01->getScale().y);
		spriteLevels[i].setTexture(*textLevels);
	}
}

int RegionMap::getMower()
{
	return selectedMow;
}

int RegionMap::getHedgeCutter()
{
	return selectedHedgeCutter;
}
