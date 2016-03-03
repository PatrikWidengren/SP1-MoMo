#include "AnimeManager.h"
#include <iostream>

AnimeManager::AnimeManager() {
	mTextureSheet.loadFromFile("Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png");
	mSpriteSheet.setTexture(mTextureSheet);
	mRects[0] = new sf::IntRect(sf::Vector2i(64 * 1.5, 64 * 8.5), sf::Vector2i(64 * 2, 64 * 2));
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
	test.addFrame(0.4f, *mRects[6]);
	animatorTest.addAnimation("test", test, sf::seconds(1.1f));
	animatorTest.playAnimation("test", true);
}

AnimeManager::~AnimeManager() {
}

void AnimeManager::playTest() {
	animatorTest.update(clock.restart());
	animatorTest.animate(mSpriteSheet);
}

sf::Sprite* AnimeManager::getSpriteSheet() {
	return &mSpriteSheet;
}
