#ifndef INCLUDED_SOUNDMANAGER
#define INCLUDED_SOUNDMANAGER

#include <SFML\Audio.hpp>
#include "AudioHandler.h"
#include <vector>
#include <string>

class SoundManager{
public:
	AudioHandler* audio = AudioHandler::instance();

	SoundManager();
	virtual ~SoundManager();
	void playSound(int id);
	void stopSound(int id);
	void setVolume(int volume);
	void loadSounds(int i);
	void load(int number, int sounds[]);
	void SoundManager::unload();
	int getVolume();
	void setParamValue(int id, const char* param, double value);
	float getParamValue(int id, const char* param);

private:
	const static int numOfSounds = 20;

	Audio* mSound[numOfSounds];
	std::string sndFile[numOfSounds];
};

#endif