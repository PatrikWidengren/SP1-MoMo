#ifndef INCLUDED_MUSICMANAGER
#define INCLUDED_MUSICMANAGER

#include "AudioHandler.h"
#include <SFML\Audio.hpp>

class MusicManager{
public:
	AudioHandler* audio = AudioHandler::instance();
	MusicManager(int id);
	virtual ~MusicManager();
	virtual Audio* getMusic();
	virtual void setMusic(int id);
	int getVolume();
	void setVolume(int volume);
private:
	//sf::Music mMusic;
	typedef std::vector<Audio*> SongList;
	SongList mSongList;
	

	int const mMaxVolume = 100; //=?
	int saveID;
	int mVolume;
};

#endif