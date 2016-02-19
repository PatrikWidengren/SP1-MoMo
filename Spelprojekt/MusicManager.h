#ifndef INCLUDED_MUSICMANAGER
#define INCLUDED_MUSICMANAGER

#include <SFML\Audio.hpp>

class MusicManager{
public:
	MusicManager(int id);
	virtual ~MusicManager();
	virtual sf::Music* getMusic();
	virtual void setMusic(int id);
	void getVolume(int volume);
	int setVolume();
private:
	sf::Music mMusic;
	int const mMaxVolume = 100;
	int mVolume;
};

#endif