#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
const int numberOfSongs = 10;
//const int numberOfBanks = 10;

//Name array = events instead, change this slask

static const string nameArray[numberOfSongs] = { "Music/Menu/Title","Music/Menu/Miyoda", "Music/Menu/WorldMap",
"Music/Levels/Generic1", "Music/Levels/Generic2", "Music/Levels/Generic3",
"Music/Levels/Ice", "Music/Levels/Temple1-7", "Music/Levels/Temple8",
 "Music/Levels/Asian" };

//static const string bankArray[numberOfBanks] = {};

MusicManager::MusicManager(int id)
{
	mVolume = 50;

	for (int i = 0; i < numberOfSongs; i++) 
	{
		Audio *a = new Audio(nameArray[i].c_str());
		mSongList.push_back(a);

		if (!a->getInstance())
		{
			std::cout << "Song: " << i << " failed to load!" << endl;
		}
		audio->setVolume(mSongList[i], mVolume);
	}
	audio->play(mSongList[id]);
	saveID = id;
}

MusicManager::~MusicManager(){
/*	int i = numberOfSongs - 1;
	while (!mSongList.empty()) {
		//mSongList[i]->stop();
		delete mSongList[i];
		mSongList.pop_back();
		i--;
	}*/
}

Audio* MusicManager::getMusic(){
	return mSongList[saveID];
}

void MusicManager::setMusic(int id){
	if (saveID != id) {
		audio->stop(mSongList[saveID]);
		audio->setVolume(mSongList[id], mVolume);
		audio->play(mSongList[id]);
		saveID = id;
	}
}

int MusicManager::getVolume() {
	return mVolume;
}

void MusicManager::setVolume(int volume) {
	mVolume = volume;
	audio->setVolume(mSongList[saveID], mVolume);;
}
