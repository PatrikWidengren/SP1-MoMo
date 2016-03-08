#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
const int numberOfSongs = 3;
static const string nameArray[numberOfSongs] = {"Resource Files/Music/Title.ogg", "Resource Files/Music/Miyoda.ogg", "Resource Files/Music/Gardenice.ogg"};

MusicManager::MusicManager(int id) {
	mVolume = 25;
	for (int i = 0; i < numberOfSongs; i++) {
		mSongList.push_back(new sf::Music);
		mSongList[i]->openFromFile(nameArray[i]);
		mSongList[i]->setVolume(mVolume);
		mSongList[i]->setLoop(true);
	}
	mSongList[id]->play();
	saveID = id;
}

MusicManager::~MusicManager(){
	while (!mSongList.empty()) {
		delete mSongList.back();
		mSongList.pop_back();
	}
}

sf::Music* MusicManager::getMusic(){
	return mSongList[saveID];
}

void MusicManager::setMusic(int id){
	if (saveID != id) {
		mSongList[saveID]->stop();
		mSongList[id]->setVolume(mVolume);
		mSongList[id]->play();
		saveID = id;
	}
}

int MusicManager::getVolume() {
	return mVolume;
}

void MusicManager::setVolume(int volume) {
	mVolume = volume;
	mSongList[saveID]->setVolume(mVolume);
}
