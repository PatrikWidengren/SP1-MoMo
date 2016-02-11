#ifndef INCLUDED_SOUNDMANAGER
#define INCLUDED_SOUNDMANAGER

#include <SFML\Audio.hpp>

class SoundManager{
public:
	SoundManager();
	virtual ~SoundManager();
	virtual void setSound(int id);
	virtual sf::Sound* getSound();
	virtual void playSound();
private:
	sf::SoundBuffer mSoundBuffer;
	sf::Sound mSound;
};

#endif