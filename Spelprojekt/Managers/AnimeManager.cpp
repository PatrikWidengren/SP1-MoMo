#include "AnimeManager.h"
#include <iostream>

static int spriteWidth = 256;
static int spriteHeight = 256;

AnimeManager::AnimeManager() {
	mTextureSheet.loadFromFile("Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png");
	mSpriteSheet.setTexture(mTextureSheet);

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
