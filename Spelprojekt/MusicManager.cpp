#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
static const string nameArray[3] = {"Resource Files/Music/test1.flac", "Resource Files/Music/test2.flac", "Resource Files/Music/test3.flac"};

MusicManager::MusicManager(int id) {
	mMusic.openFromFile(nameArray[id]);
}

MusicManager::~MusicManager(){
}

sf::Music* MusicManager::getMusic(){
	return &mMusic;
}

void MusicManager::setMusic(int id){
	mMusic.openFromFile(nameArray[id]);
}