#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;


//Name array = events instead, change this slask



//static const string bankArray[numberOfBanks] = {};

MusicManager::MusicManager(const char* songTitle)
{
	mSong = new Audio(songTitle);
	audio->play(mSong);
	mSaveSong = songTitle;
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
	return mSong;
}


void MusicManager::setMusic(const char* songTitle)
{
	if (songTitle != mSaveSong) {
		audio->stop(mSong);
		delete mSong;
		mSong = new Audio(songTitle);
		audio->play(mSong);
		mSaveSong = songTitle;
	}
}

void MusicManager::setVolume(int volume) {
	audio->setVolume(mSong, volume);;
}
