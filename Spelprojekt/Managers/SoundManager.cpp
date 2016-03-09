#include "SoundManager.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

const int numberOfSounds = 107;

using namespace std;
int asd;
static const string nameArray[numberOfSounds] = {
	"Resource Files/Sound/collision_vase.flac",		//0
	"Resource Files/Sound/collision_fence.flac",	//1
	"Resource Files/Sound/collision_stone.flac",	//2
	"Resource Files/Sound/collision_hedge.flac",	//3
	"Resource Files/Sound/collision_tree.flac",		//4
	"Resource Files/Sound/collision_vase.flac",		//5
	"Resource Files/Sound/collision_vase.flac",		//6
	"Resource Files/Sound/collision_vase.flac",		//7
	"Resource Files/Sound/collision_vase.flac",		//8
	"Resource Files/Sound/collision_vase.flac",		//9
	"Resource Files/Sound/collision_fence.flac",	//10
	"Resource Files/Sound/collision_fence.flac",	//11
	"Resource Files/Sound/collision_fence.flac",	//12
	"Resource Files/Sound/collision_fence.flac",	//13
	"Resource Files/Sound/collision_fence.flac",	//14
	"Resource Files/Sound/collision_fence.flac",	//15
	"Resource Files/Sound/collision_fence.flac",	//16
	"Resource Files/Sound/collision_fence.flac",	//17
	"Resource Files/Sound/collision_fence.flac",	//18
	"Resource Files/Sound/collision_fence.flac",	//19
	"Resource Files/Sound/collision_vase.flac",		//20
	"Resource Files/Sound/collision_vase.flac",		//21
	"Resource Files/Sound/collision_vase.flac",		//22
	"Resource Files/Sound/collision_vase.flac",		//23
	"Resource Files/Sound/collision_vase.flac",		//24
	"Resource Files/Sound/collision_vase.flac",		//25
	"Resource Files/Sound/collision_vase.flac",		//26
	"Resource Files/Sound/collision_vase.flac",		//27
	"Resource Files/Sound/collision_vase.flac",		//28
	"Resource Files/Sound/collision_vase.flac",		//29
	"Resource Files/Sound/collision_stone.flac",	//30
	"Resource Files/Sound/collision_stone.flac",	//31
	"Resource Files/Sound/collision_stone.flac",	//32
	"Resource Files/Sound/collision_stone.flac",	//33
	"Resource Files/Sound/collision_stone.flac",	//34
	"Resource Files/Sound/collision_stone.flac",	//35
	"Resource Files/Sound/collision_stone.flac",	//36
	"Resource Files/Sound/collision_stone.flac",	//37
	"Resource Files/Sound/collision_stone.flac",	//38
	"Resource Files/Sound/collision_stone.flac",	//39
	"Resource Files/Sound/collision_tree.flac",		//40
	"Resource Files/Sound/collision_tree.flac",		//41
	"Resource Files/Sound/collision_tree.flac",		//42
	"Resource Files/Sound/collision_tree.flac",		//43
	"Resource Files/Sound/collision_tree.flac",		//44
	"Resource Files/Sound/collision_tree.flac",		//45
	"Resource Files/Sound/collision_tree.flac",		//46
	"Resource Files/Sound/collision_tree.flac",		//47
	"Resource Files/Sound/collision_tree.flac",		//48
	"Resource Files/Sound/collision_tree.flac",		//49
	"Resource Files/Sound/MeepTest_Hello.flac",		//50
	"Resource Files/Sound/MeepTest_Hello.flac",		//51
	"Resource Files/Sound/MeepTest_Hello.flac",		//52
	"Resource Files/Sound/MeepTest_Hello.flac",		//53
	"Resource Files/Sound/MeepTest_Hello.flac",		//54
	"Resource Files/Sound/MeepTest_Hello.flac",		//55
	"Resource Files/Sound/MeepTest_Hello.flac",		//56
	"Resource Files/Sound/MeepTest_Hello.flac",		//57
	"Resource Files/Sound/MeepTest_Hello.flac",		//58
	"Resource Files/Sound/MeepTest_Hello.flac",		//59
	"Resource Files/Sound/katt.flac",				//60
	"Resource Files/Sound/katt.flac",				//61
	"Resource Files/Sound/katt.flac",				//62
	"Resource Files/Sound/katt.flac",				//63
	"Resource Files/Sound/katt.flac",				//64
	"Resource Files/Sound/katt.flac",				//65
	"Resource Files/Sound/katt.flac",				//66
	"Resource Files/Sound/katt.flac",				//67
	"Resource Files/Sound/katt.flac",				//68
	"Resource Files/Sound/katt.flac",				//69
	"Resource Files/Sound/collision_guard_1.flac",	//70
	"Resource Files/Sound/collision_guard_2.flac",	//71
	"Resource Files/Sound/collision_guard_3.flac",	//72
	"Resource Files/Sound/collision_guard_4.flac",	//73
	"Resource Files/Sound/collision_guard_1.flac",	//74
	"Resource Files/Sound/collision_guard_2.flac",	//75
	"Resource Files/Sound/collision_guard_3.flac",	//76
	"Resource Files/Sound/collision_guard_4.flac",	//77
	"Resource Files/Sound/collision_guard_3.flac",	//78
	"Resource Files/Sound/collision_guard_4.flac",	//79
	"Resource Files/Sound/collision_vase.flac",		//80
	"Resource Files/Sound/collision_vase.flac",		//81
	"Resource Files/Sound/collision_vase.flac",		//82
	"Resource Files/Sound/collision_vase.flac",		//83
	"Resource Files/Sound/collision_vase.flac",		//84
	"Resource Files/Sound/collision_vase.flac",		//85
	"Resource Files/Sound/collision_vase.flac",		//86
	"Resource Files/Sound/collision_vase.flac",		//87
	"Resource Files/Sound/collision_vase.flac",		//88
	"Resource Files/Sound/collision_vase.flac",		//89
	"Resource Files/Sound/collision_hedge.flac",	//90
	"Resource Files/Sound/collision_hedge.flac",	//91
	"Resource Files/Sound/collision_hedge.flac",	//92
	"Resource Files/Sound/collision_hedge.flac",	//93
	"Resource Files/Sound/collision_hedge.flac",	//94
	"Resource Files/Sound/collision_hedge.flac",	//95
	"Resource Files/Sound/collision_hedge.flac",	//96
	"Resource Files/Sound/collision_hedge.flac",	//97
	"Resource Files/Sound/collision_hedge.flac",	//98
	"Resource Files/Sound/collision_hedge.flac",	//99
	"Resource Files/Sound/collision_vase.flac",		//100
	"Resource Files/Sound/Meny_Close.flac",			//101
	"Resource Files/Sound/Meny_GoBack.flac",		//102
	"Resource Files/Sound/Meny_Open.flac",			//103
	"Resource Files/Sound/Lawnmower_Loop.flac",		//104
	"Resource Files/Sound/Lawnmower_Start.flac",	//105
	"Resource Files/Sound/Lawnmower_Stop.flac"		//106
};

SoundManager::SoundManager(){
	mVolume = 50;
	for (int i = 0; i < numberOfSounds; i++){
		mSoundBufferList.push_back(new sf::SoundBuffer);
		while (!mSoundBufferList[i]->loadFromFile(nameArray[i])) {
			std::cout << "Sound: " << i << " failed to load!" << endl;
		}
		mSoundList.push_back(new sf::Sound);
		mSoundList[i]->setBuffer(*mSoundBufferList[i]);
		mSoundList[i]->setVolume(mVolume);
	}
}

SoundManager::~SoundManager() {
	int i = numberOfSounds-1;
	while (!mSoundList.empty()) {
		//mSoundList[i]->stop();
		delete mSoundList[i];
		mSoundList.pop_back();
		i--;
	}
	i = numberOfSounds-1;
	while (!mSoundBufferList.empty()) {
		delete mSoundBufferList[i];
		mSoundBufferList.pop_back();
		i--;
	}
}


void SoundManager::playSound(float id){
	float tempTest = id * 10;
	int temp = (int)tempTest;
	if (temp >= 70 && temp <= 79) {
		int i = (rand() % 10)+70;
		temp = i;
	}
	cout << endl << temp << ", " << id << endl;
	if (temp >= 0 && temp <= numberOfSounds) {
		mSoundList[temp]->play();
	}
	if (temp >= 105 && temp <= 106) {
		mSoundList[temp]->play();
	}
	if (temp >= 104 && temp <= 104) {
		mSoundList[temp]->setLoop(true);
		mSoundList[temp]->play();
	}
}

void SoundManager::stopSound(float id) {
	float tempTest = id * 10;
	int temp = (int)tempTest;
	mSoundList[temp]->stop();
}

void SoundManager::setVolume(int volume){
	mVolume = volume;
	for (int i = 0; i < numberOfSounds; i++){
		mSoundList[i]->setVolume(mVolume);
	}
}

int SoundManager::getVolume() {
	return mVolume;
}
