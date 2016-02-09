#include "MusicManager.h"
#include <iostream>
#include <string>

using namespace std;
static const string nameArray[3] = {"test1.flac", "test2.flac", "test3.flac"};

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