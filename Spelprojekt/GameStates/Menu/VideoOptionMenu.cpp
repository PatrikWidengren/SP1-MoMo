#include "VideoOptionMenu.h"

VideoOptionMenu::VideoOptionMenu(float width, float height)
{
	mTimer = 0;
	mState = 4;
	mOptionMenuState = 2;
	setFonts();
	setTextures();

	spriteCheckbox01->setPosition(200, 600);
	spriteCheckbox02->setPosition(200, 800);

	spriteBg01->setPosition(0, 0);
	spriteIngameOption->setPosition(0, 0);


	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(200, 600), sf::Vector2i(128, 128));
	mRects[1] = new sf::IntRect(sf::Vector2i(200, 800), sf::Vector2i(128, 128));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385, 515), sf::Vector2i(113, 91));	
}

VideoOptionMenu::~VideoOptionMenu()
{
	delete textCheckBox;
	delete textBg01;

	delete textInGameOption;

	delete textBack;
	delete textHighlightBack;

	delete spriteCheckbox01;
	delete spriteCheckbox02;

	delete spriteBack;

	delete spriteBg01;
	delete spriteIngameOption;

}

void VideoOptionMenu::updateVideoOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound)
{

	mMouse.x = mouse.x;
	mMouse.y = mouse.y;
	if (mFullscreen)
	{
		spriteCheckbox01->setColor(sf::Color(255, 255, 255, 255));
		spriteCheckbox02->setColor(sf::Color(155, 155, 155, 100));
		mSwap = true;
	}
	else if (!mFullscreen)
	{
		spriteCheckbox02->setColor(sf::Color(255, 255, 255, 255));
		spriteCheckbox01->setColor(sf::Color(155, 155, 155, 100));
		mSwap = false;

	
	}

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mFullscreen = true;
			mClick = false;
			sound.playSound(10.1);
		}
	}


	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mFullscreen = false;
			mClick = false;
			sound.playSound(10.1);
		}
	}

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteBack->setTexture(*textHighlightBack);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mOptionMenuState = 1;
			sound.playSound(10.1);
		}
	}
	else
		spriteBack->setTexture(*textBack);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void VideoOptionMenu::displayMenu01(sf::RenderWindow &window)
{

	window.draw(*spriteBg01);
	window.draw(*spriteBack);
	window.draw(*spriteIngameOption);

	window.draw(*spriteCheckbox01);
	window.draw(*spriteCheckbox02);


}

void VideoOptionMenu::setTextures()
{

	if (!textBg01->loadFromFile("Resource Files/Backgrounds/Background.png")) //try to load the texture. if its wrong, give error
		textBg01->loadFromFile("error.jpg");

	if (!textInGameOption->loadFromFile("Resource Files/Backgrounds/InGame_Options.png")) //try to load the texture. if its wrong, give error
		textInGameOption->loadFromFile("error.jpg");

	if (!textCheckBox->loadFromFile("Resource Files/Menus/Confirm.png"))
		textCheckBox->loadFromFile("error.jpg");

	if (!textHighlightBack->loadFromFile("Resource Files/Menus/BackArrow_Highlight.png"))
		textHighlightBack->loadFromFile("error.jpg");
	if (!textBack->loadFromFile("Resource Files/Menus/BackArrow.png"))
		textBack->loadFromFile("error.jpg");


	spriteBack->setTexture(*textBack);

	spriteCheckbox01->setTexture(*textCheckBox);
	spriteCheckbox02->setTexture(*textCheckBox);

	spriteBg01->setTexture(*textBg01);

	spriteIngameOption->setTexture(*textInGameOption);

}

void VideoOptionMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void VideoOptionMenu::moveUp()
{

}

void VideoOptionMenu::moveDown()
{

}


int VideoOptionMenu::checkState() {
	return mState;
}

int VideoOptionMenu::checkOptionState() {
	return mOptionMenuState;
}

void VideoOptionMenu::scale(sf::RenderWindow &window) {

	mState = 4;
	mOptionMenuState = 4;

	spriteBg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(200 * bg01->getScale().x, 600 * bg01->getScale().y), sf::Vector2i(128 * bg01->getScale().x, 128 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(200 * bg01->getScale().x, 800 * bg01->getScale().y), sf::Vector2i(128 * bg01->getScale().x, 128 * bg01->getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385 * bg01->getScale().x, 515 * bg01->getScale().y), sf::Vector2i(113 * bg01->getScale().x, 91 * bg01->getScale().y));

	spriteBack->setPosition(1385 * bg01->getScale().x, 515 * bg01->getScale().y);
	spriteIngameOption->setPosition(0 * bg01->getScale().x, 300 * bg01->getScale().y);


	spriteCheckbox01->setPosition(200 * bg01->getScale().x, 600 * bg01->getScale().y);
	spriteCheckbox02->setPosition(200 * bg01->getScale().x, 800 * bg01->getScale().y);
}

bool VideoOptionMenu::getFullscreen()
{
	return mFullscreen;
}

bool VideoOptionMenu::getSwap()
{
	return mSwap;
}