#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
const int numberOfSongs = 10;
//const int numberOfBanks = 10;

//Name array = events instead, change this slask

static const string nameArray[numberOfSongs] = {"event:/Music/Menu/Title","event:/Music/Menu/Miyoda", "event:/Music/Menu/WorldMap",
"event:/Music/Menu/Levels/Generic1", "event:/Music/Menu/Levels/Generic2", "event:/Music/Menu/Levels/Generic3",
"event:/Music/Menu/Levels/Ice", "event:/Music/Menu/Levels/Temple1-7", "event:/Music/Menu/Levels/Temple8",
 "event:/Music/Menu/Levels/Asian" };

//static const string bankArray[numberOfBanks] = {};

MusicManager::MusicManager(int id)
{
/*[21:02:45] Zas: load the audio bank
[21:03:32] Zas: then 
[20:59] Slask: 

<<<   mSongList.push_back(new sf::Music);
  while (!mSongList[i]->openFromFile(nameArray[i])) {turns into
[21:04:22] Zas: Audio *a=new Audio(nameArray[i]);
[21:04:37] Zas: why is that a while loop though
[21:04:43] Zas: but you'd first do a new audio
[21:04:51] Zas: then check if it loaded and then push it back
[21:04:55 | Redigerat 21:05:00] Zas: push_back(a );*/

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
		//Fixa loop här Slask
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
