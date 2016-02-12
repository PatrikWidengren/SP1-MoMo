#include "HedgeCutter.h"
#include <iostream>

HedgeCutter::HedgeCutter(int reach, int max){
	mReach = reach;
	mMaxDistance = max;
}

HedgeCutter::~HedgeCutter(){

}

bool HedgeCutter::stopMove(){
	return false;
}

int HedgeCutter::getReach(){
	return mReach;
}

cutVector HedgeCutter::getCuts(int arrX, int arrY){
	while (!curCuts.empty()){
		curCuts.pop_back();
	}
	int tempReach = mReach;
	mBaseTile[0] = { arrX};
	mBaseTile[1] = { arrY };
	if (tempReach > 0){
		calcCuts(mBaseTile, tempReach);
	}
	
	for (cutVector::size_type i = 0; i < curCuts.size(); i++){
		
	}
	return curCuts;
}

void HedgeCutter::calcCuts(coords base, int temp){
	temp--;
	//Get backup so we don't lose the original value
	coords baseBackup = base;
	for (int i = 0; i < 4; i++){
		//reset the base to the backup every loop so we get the right coordinates
		base = baseBackup;
		switch (i){
		case 0:
			//Set the coordinates to be cut
			base[0]--;
			//Make sure the coordinate isn't cut already
			if (std::find(curCuts.begin(), curCuts.end(), base) != curCuts.end()) {
			}
			else {
				//Make sure it doesn't reach too far out in any direction
				if (mBaseTile[0] - base[0] < -mMaxDistance ||
					mBaseTile[0] - base[0] > mMaxDistance ||
					mBaseTile[1] - base[1] < -mMaxDistance ||
					mBaseTile[1] - base[1] > mMaxDistance){
				}
				else {
					//if it checks out, add it to the cutVector
					curCuts.push_back(base);
				}
			}
			//If we haven't reached max range yet, keep looping
			if (temp > 0){
				calcCuts(base, temp);
			}
			break;
		case 1:
			//Set the coordinates to be cut
			base[1]--;
			//Make sure the coordinate isn't cut already
			if (std::find(curCuts.begin(), curCuts.end(), base) != curCuts.end()) {
			}
			else {
				//Make sure it doesn't reach too far out in any direction
				if (mBaseTile[0] - base[0] < -mMaxDistance ||
					mBaseTile[0] - base[0] > mMaxDistance ||
					mBaseTile[1] - base[1] < -mMaxDistance ||
					mBaseTile[1] - base[1] > mMaxDistance){
				}
				else {
					//if it checks out, add it to the cutVector
					curCuts.push_back(base);
				}
			}
			//If we haven't reached max range yet, keep looping
			if (temp > 0){
				calcCuts(base, temp);
			}
			break;
		case 2:
			//Set the coordinates to be cut
			base[0]++;
			//Make sure the coordinate isn't cut already
			if (std::find(curCuts.begin(), curCuts.end(), base) != curCuts.end()) {
			}
			else {
				//Make sure it doesn't reach too far out in any direction
				if (mBaseTile[0] - base[0] < -mMaxDistance ||
					mBaseTile[0] - base[0] > mMaxDistance ||
					mBaseTile[1] - base[1] < -mMaxDistance ||
					mBaseTile[1] - base[1] > mMaxDistance){
				}
				else {
					//if it checks out, add it to the cutVector
					curCuts.push_back(base);
				}
			}
			//If we haven't reached max range yet, keep looping
			if (temp > 0){
				calcCuts(base, temp);
			}
			break;
		case 3:
			//Set the coordinates to be cut
			base[1]++;
			//Make sure the coordinate isn't cut already
			if (std::find(curCuts.begin(), curCuts.end(), base) != curCuts.end()) {
			}
			else {
				//Make sure it doesn't reach too far out in any direction
				if (mBaseTile[0] - base[0] < -mMaxDistance ||
					mBaseTile[0] - base[0] > mMaxDistance ||
					mBaseTile[1] - base[1] < -mMaxDistance ||
					mBaseTile[1] - base[1] > mMaxDistance){
				}
				else {
					//if it checks out, add it to the cutVector
					curCuts.push_back(base);
				}
			}
			//If we haven't reached max range yet, keep looping
			if (temp > 0){
				calcCuts(base, temp);
			}
			break;
		}
	}
}