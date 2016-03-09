#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
const int numberOfSongs = 9;
static const string nameArray[numberOfSongs] = {"Resource Files/Music/Title.ogg", "Resource Files/Music/Miyoda.ogg", "Resource Files/Music/Worldmap.ogg",
"Resource Files/Music/GardenGeneric1.ogg", "Resource Files/Music/GardenGeneric2.ogg", "Resource Files/Music/GardenGeneric3.ogg",
"Resource Files/Music/Gardenice.ogg", "Resource Files/Music/GardenTemple1-7.ogg", "Resource Files/Music/GardenTemple8.ogg" };

MusicManager::MusicManager(int id) {
	mVolume = 25;
	for (int i = 0; i < numberOfSongs; i++) {
		mSongList.push_back(new sf::Music);
		while (!mSongList[i]->openFromFile(nameArray[i])) {
			std::cout << "Song: " << i << " failed to load!" << endl;
		}
		mSongList[i]->setVolume(mVolume);
		mSongList[i]->setLoop(true);
	}
	mSongList[id]->play();
	saveID = id;
}

MusicManager::~MusicManager(){
	int i = numberOfSongs - 1;
	while (!mSongList.empty()) {
		mSongList[i]->stop();
		mSongList[i]->~Music();
		mSongList.pop_back();
		i--;
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
