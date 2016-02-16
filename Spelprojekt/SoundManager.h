#ifndef INCLUDED_SOUNDMANAGER
#define INCLUDED_SOUNDMANAGER

#include <SFML\Audio.hpp>
#include <vector>
#include <string>

class SoundManager{
public:
	SoundManager();
	virtual ~SoundManager();
	virtual void playSound(float id);
private:
	static const std::string mNameArray[2];
	sf::SoundBuffer mSoundBuffer;
	typedef std::vector<sf::Sound*> SoundList;
	SoundList mSoundList;
};

#endif