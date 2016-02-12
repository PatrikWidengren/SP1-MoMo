#include "SoundManager.h"
#include <iostream>
#include <string>

using namespace std;
static const string nameArray[3] = { "Resource Files/Sound/Placeholder.ogg", "Resource Files/Music/test1.flac", "Resource Files/Music/test1.flac" };

SoundManager::SoundManager() {
}

SoundManager::~SoundManager(){
}

void SoundManager::setSound(int id){
	mSoundBuffer.loadFromFile(nameArray[id]);
	mSound.setBuffer(mSoundBuffer);
}

sf::Sound* SoundManager::getSound(){
	return &mSound;
}

void SoundManager::playSound(){
	mSound.play();
}

