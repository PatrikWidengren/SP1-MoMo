#include "AnimeManager.h"
#include <iostream>

static int spriteWidth = 256;
static int spriteHeight = 256;

AnimeManager::AnimeManager() {
	mTextureSheet.loadFromFile("Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png");
	mSpriteSheet.setTexture(mTextureSheet);

	/*mRects = new sf::IntRect(sf::Vector2i(64 * 1.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[1] = new sf::IntRect(sf::Vector2i(64 * 5.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[2] = new sf::IntRect(sf::Vector2i(64 * 9.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[3] = new sf::IntRect(sf::Vector2i(64 * 13.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[4] = new sf::IntRect(sf::Vector2i(64 * 17.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[5] = new sf::IntRect(sf::Vector2i(64 * 21.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	mRects[6] = new sf::IntRect(sf::Vector2i(64 * 25.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
	test.addFrame(0.4f, *mRects[0]);
	test.addFrame(0.4f, *mRects[1]);
	test.addFrame(0.4f, *mRects[2]);
	test.addFrame(0.4f, *mRects[3]);
	test.addFrame(0.4f, *mRects[4]);
	test.addFrame(0.4f, *mRects[5]);
	test.addFrame(0.4f, *mRects[6]);*/

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation test;
		for (int i = 0; i < 7; i++) {
			mRects = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			test.addFrame(0.4f, *mRects);
		}
		std::ostringstream tempName;
		tempName << "idle" << j + 1;
		animatorTest.addAnimation(tempName.str(), test, sf::seconds(1.1f));
	}
	animatorTest.playAnimation("idle3", true);
}
AnimeManager::~AnimeManager() {
}

void AnimeManager::changeAnimation(std::string name) {
	animatorTest.playAnimation(name, true);
}

void AnimeManager::playTest() {
	animatorTest.update(clock.restart());
	animatorTest.animate(mSpriteSheet);
}

sf::Sprite* AnimeManager::getSpriteSheet() {
	return &mSpriteSheet;
}
