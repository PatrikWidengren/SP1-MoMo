#ifndef INCLUDED_MUSICMANAGER
#define INCLUDED_MUSICMANAGER

#include "AudioHandler.h"
#include <SFML\Audio.hpp>

class MusicManager{
public:
	AudioHandler* audio = AudioHandler::instance();
	MusicManager(const char* songTitle);
	virtual ~MusicManager();
	virtual Audio* getMusic();
	virtual void setMusic(const char* songTitle);
	int getVolume();
	void setVolume(int volume);
private:
	//sf::Music mMusic;
	Audio* mSong;

	int const mMaxVolume = 100; //=?
	int mVolume;
	const char* mSaveSong;
};

#endif