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
	void getVolume(int volume);
	int setVolume();
private:
	static const std::string mNameArray[2];
	typedef std::vector<sf::SoundBuffer*> SoundBufferList;
	SoundBufferList mSoundBufferList;
	typedef std::vector<sf::Sound*> SoundList;
	SoundList mSoundList;
	int const mMaxVolume = 100;
	int mVolume;
};

#endif