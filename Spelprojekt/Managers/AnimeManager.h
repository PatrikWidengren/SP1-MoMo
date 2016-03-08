#ifndef INCLUDED_ANIMEMANAGER
#define INCLUDED_ANIMEMANAGER

#include <Thor\Animations.hpp>
#include <SFML\Graphics.hpp>
#include <sstream>

class AnimeManager {
public:
	AnimeManager();
	virtual ~AnimeManager();
	sf::Sprite* getSpriteSheet();
	void playTest();
	void changeAnimation(std::string name);
private:
	sf::Clock clock;
	thor::Animator<sf::Sprite, std::string> animatorTest;
	sf::Texture mTextureSheet;
	sf::Sprite mSpriteSheet;
	thor::FrameAnimation* test;
	sf::IntRect *mRects;
};

#endif