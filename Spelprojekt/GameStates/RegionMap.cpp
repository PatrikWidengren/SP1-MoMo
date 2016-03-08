#include "RegionMap.h"
#include <sstream>

RegionMap::RegionMap(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
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



	spriteShop.setPosition(0, 1080);
	spriteArrow01.setPosition(120, 850);
	spriteArrow01.setScale(-1, 1);
	spriteArrow02.setPosition(285, 850);
	spriteArrow03.setPosition(610, 850);
	spriteArrow03.setScale(-1, 1);
	spriteArrow04.setPosition(775, 850);

	spriteHedgecutter.setPosition(630, 850);
	
	spriteGrassMower.setPosition(140, 850);

	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));

	mRects[3] = new sf::IntRect(sf::Vector2i(3, 850), sf::Vector2i(116, 173));
	mRects[4] = new sf::IntRect(sf::Vector2i(285, 850), sf::Vector2i(116, 180));
	mRects[5] = new sf::IntRect(sf::Vector2i(493, 850), sf::Vector2i(116, 173));
	mRects[6] = new sf::IntRect(sf::Vector2i(775, 850), sf::Vector2i(116, 180));

}

RegionMap::RegionMap()
{

}

RegionMap::~RegionMap()
{

}

void RegionMap::updateRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	switch (mInternalState) {
	case 0: //nothing visible, yet

		//if (spriteShop.getPosition().y >= 1080 * bg01.getScale().y)

		spriteShop.setPosition(0 * bg01.getScale().x, 1080 * bg01.getScale().y);

		spriteArrow01.setPosition(120 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 1120 * bg01.getScale().y);

		spriteGrassMower.setPosition(140 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteHedgecutter.setPosition(630 * bg01.getScale().x, 1120 * bg01.getScale().y);
		
		mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));

		break;

	case 1: //Level select visible

		if (spriteShop.getPosition().y < window.getSize().y)
		{
			spriteShop.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);

			spriteGrassMower.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteHedgecutter.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);

			mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
			mRects[4] = new sf::IntRect(sf::Vector2i(287 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
			mRects[7] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
			mRects[6] = new sf::IntRect(sf::Vector2i(777 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));

		}


		//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
		break;


	case 2: //Shop visible

		if (spriteShop.getPosition().y >= window.getSize().y - spriteShop.getGlobalBounds().height)
		{
			spriteShop.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);

			spriteGrassMower.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteHedgecutter.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);



		}
		mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 830 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 830 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 830 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 830 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));


		break;
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

	if (mInternalState == 1) {
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		if (mLevelRects[i].contains(sf::Vector2i(mMouse.x, mMouse.y))) {
			std::cout << "It's inside " << i << "!" << std::endl;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
					mLevelToLoad = i + 1;
				mState = 8;
			}
		}
	}
	}

#pragma region ArrowRects
	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow01.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedMow >= 1)
			{
				selectedMow--;
			}
			spriteGrassMower.setTexture(textMowers[selectedMow]);

		}
		else
			spriteArrow01.setTexture(textArrow01);
	}

	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow02.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedMow < 2)
			{
				selectedMow++;
			}
			spriteGrassMower.setTexture(textMowers[selectedMow]);
		}
		else
			spriteArrow02.setTexture(textArrow01);
	}


	if (mRects[5]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow03.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedHedgeCutter >= 1)
			{
				selectedHedgeCutter--;
			}
			spriteHedgecutter.setTexture(textHedgecutters[selectedHedgeCutter]);
		}
		else
			spriteArrow03.setTexture(textArrow01);

	}


	if (mRects[6]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow04.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedHedgeCutter < 1)
			{
				selectedHedgeCutter++;
			}
			spriteHedgecutter.setTexture(textHedgecutters[selectedHedgeCutter]);

		}
		else
			spriteArrow04.setTexture(textArrow01);
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
	window.draw(bg01);
	window.draw(spriteShop);
	window.draw(spriteArrow01);
	window.draw(spriteArrow02);
	window.draw(spriteArrow03);
	window.draw(spriteArrow04);
	window.draw(spriteHedgecutter);
	window.draw(spriteGrassMower);
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

	if (!textLevels.loadFromFile("Resource Files/Menus/LevelPick.png"))
		textureShop.loadFromFile("error.jpg");

	if (!textureShop.loadFromFile("Resource Files/Menus/Shop_temp.png"))
		textureShop.loadFromFile("error.jpg");

	if (!textArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right.png"))
		textArrow01.loadFromFile("error.jpg");

	if (!textHighlightArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right_Highlight.png"))
		textHighlightArrow01.loadFromFile("error.jpg");
#pragma region Set Textures Mowers

	if (!textMowers[0].loadFromFile("Resource Files/Sprites/Mowers/mow0.png"))
		textMowers[0].loadFromFile("error.jpg");
	if (!textMowers[1].loadFromFile("Resource Files/Sprites/Mowers/mow1.png"))
		textMowers[1].loadFromFile("error.jpg");
	if (!textMowers[2].loadFromFile("Resource Files/Sprites/Mowers/mow2.png"))
		textMowers[2].loadFromFile("error.jpg");


	if (!textHedgecutters[0].loadFromFile("Resource Files/Sprites/Hedgecutters/hedgecutter0.png"))
		textHedgecutters[0].loadFromFile("error.jpg");
	if (!textHedgecutters[1].loadFromFile("Resource Files/Sprites/Hedgecutters/hedgecutter1.png"))
		textHedgecutters[1].loadFromFile("error.jpg");

	spriteGrassMower.setTexture(textMowers[0]);
	spriteHedgecutter.setTexture(textHedgecutters[0]);

#pragma endregion

	spriteArrow01.setTexture(textArrow01);
	spriteArrow02.setTexture(textArrow01);
	spriteArrow03.setTexture(textArrow01);
	spriteArrow04.setTexture(textArrow01);
	
	bg01.setTexture(textBackgrounds[mRegionState]);
	spriteShop.setTexture(textureShop);


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
	/*if (selectedIndex - 1 >= 0)
	{
	menu[selectedIndex].setColor(sf::Color::White);
	selectedIndex--;
	menu[selectedIndex].setColor(sf::Color::Red);
	}*/
}

void RegionMap::moveDown()
{
	/*if (selectedIndex + 1 < mNumberOfSelections)
	{
	menu[selectedIndex].setColor(sf::Color::White);
	selectedIndex++;
	menu[selectedIndex].setColor(sf::Color::Red);
	}*/

}

int RegionMap::checkState()
{
	return mState;
}

int RegionMap::checkRegionState() {
	return mRegionState;
}

void RegionMap::setRegionState(int state) {
	if (mLevelRects != 0)
	delete[] mLevelRects;

	if (spriteLevels != 0)
	delete[] spriteLevels;

	mRegionState = state;
	bg01.setTexture(textBackgrounds[mRegionState]);
	spriteLevels = new sf::Sprite[mRegions[mRegionState].levelCount];
	mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		mLevelRects[i] = sf::IntRect(sf::Vector2i(0 * bg01.getScale().x, i * 100 * bg01.getScale().y), sf::Vector2i(200 * bg01.getScale().x, 100 * bg01.getScale().y));
	}

	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		spriteLevels[i].setPosition(0 * bg01.getScale().x, i * 100 * bg01.getScale().y);
		spriteLevels[i].setScale(bg01.getScale().x, bg01.getScale().y);
		spriteLevels[i].setTexture(textLevels);
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

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	/*	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));
	*/

	spriteShop.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteGrassMower.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow01.setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow02.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow03.setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow04.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		spriteLevels[i].setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	}


	mRects[0] = new sf::IntRect(sf::Vector2i(360 * bg01.getScale().x, 295 * bg01.getScale().y), sf::Vector2i(410 * bg01.getScale().x, 200 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(925 * bg01.getScale().x, 300 * bg01.getScale().y), sf::Vector2i(395 * bg01.getScale().x, 200 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660 * bg01.getScale().x, 75 * bg01.getScale().y), sf::Vector2i(180 * bg01.getScale().x, 145 * bg01.getScale().y));
	mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 850 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 850 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
	mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 850 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
	mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 850 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
	
	if (mInternalState == 1) {
		spriteShop.setPosition(0 * bg01.getScale().x, 780 * bg01.getScale().y);
		spriteGrassMower.setPosition(140 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow01.setPosition(120 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 550 * bg01.getScale().y);
	}
	else {
		spriteShop.setPosition(0 * bg01.getScale().x, 1080 * bg01.getScale().y);
		spriteGrassMower.setPosition(140 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow01.setPosition(120 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 850 * bg01.getScale().y);
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
