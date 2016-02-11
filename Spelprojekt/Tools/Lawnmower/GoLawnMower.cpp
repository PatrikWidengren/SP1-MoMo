#include "GoLawnMower.h"

/*GoLawnMower with specified statblock*/
GoLawnMower::GoLawnMower(int max, int min, int rise, int fall, int durability) {
	mStats.mMaxMom=max;
	mStats.mMinMom=min;
	mStats.mRise=rise;
	mStats.mFall=fall;
	mStats.mDurability = durability;
	/*mLastDir is initiated to ensure we don't get an error.
	0 will never be read as a valid direction elsewhere, ensuring
	no strange behaviours*/
	mLastDir = 0;
	/*initializing mCurMom to guard against errors at the start of a game
	when meep hasn't moved yet*/
	mCurMom = mStats.mMinMom;
}

/*standardvalues for GoLawnMower if nothing is specified*/
GoLawnMower::GoLawnMower() {
	mStats.mMaxMom = 6;
	mStats.mMinMom = 1;
	mStats.mRise = 2;
	mStats.mFall = 4;
	mStats.mDurability = 20;
	/*mLastDir is initiated to ensure we don't get an error.
	0 will never be read as a valid direction elsewhere, ensuring
	no strange behaviours*/
	mLastDir = 0;
	/*initializing mCurMom to guard against errors at the start of a game
	when meep hasn't moved yet*/
	mCurMom = mStats.mMinMom;
}

GoLawnMower::~GoLawnMower(){
}

void GoLawnMower::momRise(mowStats stats){
	/*A bit needlessly complicated to ensure that mCurMom is
	never given a faulty value*/
	if (mCurMom + stats.mRise >= stats.mMaxMom){
		mCurMom = stats.mMaxMom;
	}
	else {
		mCurMom += stats.mRise;
	}
}
void GoLawnMower::momFall(mowStats stats){
	/*A bit needlessly complicated to ensure that mCurMom is
	never given a faulty value*/
	if (mCurMom - stats.mFall <= stats.mMinMom){
		mCurMom = stats.mMinMom;
	}
	else {
		mCurMom -= stats.mFall;
	}
}

/*Function exists purely so the user only needs a single function call
to get the movement, and so that decorator can make the move without
determining momentum twice*/
intVector GoLawnMower::getMove(int dir){
	if (mStats.mFunctioning){
		/*increase or decrease momentum*/
		determineMom(dir, mStats);
		/*create a list of steps to attempt*/
		intVector curMove = writeMove(dir);
		/*mLastDir updated last to ensure other getMove() functions
		can maintain the same structure while utilising both dir and mLastDir*/
		mLastDir = dir;
		return curMove;
	}
	else {
		intVector curMove;
		return curMove;
	}
}

intVector GoLawnMower::writeMove(int dir){
	intVector curMove;
	for (int i = 0; i < mCurMom; i++){
		curMove.push_back(dir);
	}
	mLastDir = dir;
	return curMove;
}

void GoLawnMower::determineMom(int dir, mowStats stats){
	/*ugly code incoming. No elegant solution found.
	GoLawnMower keeps rising if the direction is adjacent or the same,
	otherwise it falls*/
	if (dir != 5 && dir != 0){
		switch (dir){
		case 1:
			if (mLastDir == 4 || mLastDir == 1 || mLastDir == 2){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 2:
			if (mLastDir == 1 || mLastDir == 2 || mLastDir == 3){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 3:
			if (mLastDir == 2 || mLastDir == 3 || mLastDir == 6){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 6:
			if (mLastDir == 3 || mLastDir == 6 || mLastDir == 9){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 9:
			if (mLastDir == 6 || mLastDir == 9 || mLastDir == 8){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 8:
			if (mLastDir == 9 || mLastDir == 8 || mLastDir == 7){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 7:
			if (mLastDir == 8 || mLastDir == 7 || mLastDir == 4){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;

		case 4:
			if (mLastDir == 7 || mLastDir == 4 || mLastDir == 1){
				momRise(stats);
			}
			else{
				momFall(stats);
			}
			break;
		}
	}
	mLastDir = dir;
}

int GoLawnMower::getMaxMom() const{
	return mStats.mMaxMom;
}

int GoLawnMower::getMinMom() const{
	return mStats.mMinMom;
}

int GoLawnMower::getRiseVal() const{
	return mStats.mRise;
}

int GoLawnMower::getFallVal() const{
	return mStats.mFall;
}

int GoLawnMower::getDurability() const{
	return mStats.mDurability;
}

bool GoLawnMower::getFunctioning() const{
	return mStats.mFunctioning;
}

int GoLawnMower::getLastDir() const{
	return mLastDir;
}

int GoLawnMower::getCurMom() const{
	return mCurMom;
}

void GoLawnMower::resetValues(){
	mCurMom = mStats.mMinMom;
	mLastDir = 0;
}

void GoLawnMower::setToMin(int dmg){
	mCurMom = mStats.mMinMom;
	mStats.mDurability -= dmg;
	if (mStats.mDurability <= 0){
		mStats.mFunctioning = false;
	}
}