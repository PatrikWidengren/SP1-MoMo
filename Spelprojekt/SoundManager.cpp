#include "SoundManager.h"
#include <iostream>
#include <string>

using namespace std;
static const string nameArray[9] = { "Resource Files/Sound/collision_fence.flac", 
	"Resource Files/Sound/collision_vase.flac",
	"Resource Files/Sound/collision_stone.flac",
	"Resource Files/Sound/collision_tree.flac",
	"Resource Files/Sound/MeepTest_Hello.flac",
	"Resource Files/Sound/katt.flac", 
	"Resource Files/Sound/Slottsvakt+3.flac",
	"Resource Files/Sound/collision_vase.flac",
	"Resource Files/Sound/collision_hedge.flac"
};

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

