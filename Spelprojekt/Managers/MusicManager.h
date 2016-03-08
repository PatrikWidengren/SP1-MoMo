#ifndef INCLUDED_MUSICMANAGER
#define INCLUDED_MUSICMANAGER

#include <SFML\Audio.hpp>

class MusicManager{
public:
	MusicManager(int id);
	virtual ~MusicManager();
	virtual sf::Music* getMusic();
	virtual void setMusic(int id);
	int getVolume();
	void setVolume(int volume);
private:
	//sf::Music mMusic;
	typedef std::vector<sf::Music*> SongList;
	SongList mSongList;
	int const mMaxVolume = 100;
	int saveID;
	int mVolume;
};

#endif