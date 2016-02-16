#include "SoundManager.h"
#include <iostream>

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

SoundManager::SoundManager(){
	for (int i = 0; i < 9; i++){
		mSoundBuffer.loadFromFile(nameArray[i]); //mNameArry har igent i sig än, ****************** ladda från txt?
		mSoundList.push_back(new sf::Sound);
		mSoundList[i]->setBuffer(mSoundBuffer);
	}
}

SoundManager::~SoundManager(){
}


void SoundManager::playSound(float id){
	asd = (int)id * 10;
	mSoundList[asd]->play();
}
