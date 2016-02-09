#ifndef INCLUDED_MUSICMANAGER
#define INCLUDED_MUSICMANAGER

#include <SFML\Audio.hpp>

class MusicManager{
public:
	MusicManager(int id);
	virtual ~MusicManager();
	virtual sf::Music* getMusic();
	virtual void setMusic(int id);
private:
	sf::Music mMusic;
};

#endif