#include "LawnMower.h"

/*Initialize the lawnmower with the selected statblock*/
LawnMower::LawnMower(int max, int min, int rise, int fall) {
	mStats.mMaxMom=max;
	mStats.mMinMom=min;
	mStats.mRise=rise;
	mStats.mFall=fall;
	/*mLastDir is initiated to ensure we don't get an error.
	0 will never be read as a valid direction elsewhere, ensuring
	no strange behaviours*/
	mLastDir = 0;
	/*initializing mCurMom to guard against errors at the start of a game
	when meep hasn't moved yet*/
	mCurMom = mStats.mMinMom;
}

/*The generic values for Old Rusty if nothing else is initialized*/
LawnMower::LawnMower() {
	mStats.mMaxMom=3;
	mStats.mMinMom=1;
	mStats.mRise=1;
	mStats.mFall=1;
	/*mLastDir is initiated to ensure we don't get an error.
	0 will never be read as a valid direction elsewhere, ensuring
	no strange behaviours*/
	mLastDir = 0;
	/*initializing mCurMom to guard against errors at the start of a game
	when meep hasn't moved yet*/
	mCurMom = mStats.mMinMom;
}

LawnMower::~LawnMower(){
}

void LawnMower::momRise(mowStats stats){
	/*A bit needlessly complicated to ensure that mCurMom is
	never given a faulty value*/
	if (mCurMom + stats.mRise >= stats.mMaxMom){
		mCurMom = stats.mMaxMom;
	}
	else {
		mCurMom += stats.mRise;
	}
}
void LawnMower::momFall(mowStats stats){
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
intVector LawnMower::getMove(int dir){
	/*increase or decrease momentum*/
	determineMom(dir, mStats);
	/*create a list of steps to attempt*/
	intVector curMove=writeMove(dir);
	return curMove;
}

intVector LawnMower::writeMove(int dir){
	intVector curMove;
	for (int i = 0; i < mCurMom; i++){
		curMove.push_back(dir);
	}
	/*mLastDir updated last to ensure other getMove() functions
	can maintain the same structure while utilising both dir and mLastDir.
	mLastDir updated in writeMove function to make sure it is updated in the
	innermost layer of lawnmowers*/
	mLastDir = dir;
	return curMove;
}

void LawnMower::determineMom(int dir, mowStats stats){
	if (dir == mLastDir){
		momRise(stats);
	}
	else{
		momFall(stats);
	}
}

int LawnMower::getMaxMom() const{
	return mStats.mMaxMom;
}

int LawnMower::getMinMom() const{
	return mStats.mMinMom;
}

int LawnMower::getRiseVal() const{
	return mStats.mRise;
}

int LawnMower::getFallVal() const{
	return mStats.mFall;
}

int LawnMower::getLastDir() const{
	return mLastDir;
}

int LawnMower::getCurMom() const{
	return mCurMom;
}

void LawnMower::resetValues(){
	mCurMom = mStats.mMinMom;
	mLastDir = 0;
}

void LawnMower::setToMin(int dmg){
	mCurMom = mStats.mMinMom;
}