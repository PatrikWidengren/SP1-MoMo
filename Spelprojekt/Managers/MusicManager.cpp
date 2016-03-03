#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
static const string nameArray[3] = {"Resource Files/Music/Title.ogg", "Resource Files/Music/Miyoda.ogg", "Resource Files/Music/Gardenice.ogg"};

MusicManager::MusicManager(int id) {
	mVolume = 50;
	mMusic.openFromFile(nameArray[id]);
	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
	saveID = id;
}

MusicManager::~MusicManager(){
}

sf::Music* MusicManager::getMusic(){
	return &mMusic;
}

void MusicManager::setMusic(int id){
	if (saveID != id) {
		mMusic.stop();
		mMusic.openFromFile(nameArray[id]);
		mMusic.setVolume(mVolume);
		mMusic.setLoop(true);
		mMusic.play();
		saveID = id;
	}
}

int MusicManager::getVolume() {
	return mVolume;
}

void MusicManager::setVolume(int volume) {
	mVolume = volume;
	mMusic.setVolume(mVolume);
}
