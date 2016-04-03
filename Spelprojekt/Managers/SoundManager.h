#ifndef INCLUDED_SOUNDMANAGER
#define INCLUDED_SOUNDMANAGER

#include <SFML\Audio.hpp>
#include <vector>
#include <string>

class SoundManager{
public:
	SoundManager();
	virtual ~SoundManager();
	void playSound(float id);
	void stopSound(float id);
	void setVolume(int volume);
	void setMowerVolume(int mowerVolume);
	int getVolume();
private:
	static const std::string mNameArray[2];
	typedef std::vector<sf::SoundBuffer*> SoundBufferList;
	SoundBufferList mSoundBufferList;
	typedef std::vector<sf::Sound*> SoundList;
	SoundList mSoundList;
	int mVolume;
	int mMowerVolume;
};

#endif