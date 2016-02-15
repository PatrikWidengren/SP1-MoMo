#include "RoyceMower.h"

RoyceMower::RoyceMower(Mower *mow) {
	/*transfer all values from mow to the current lawnmower*/
	mStats.mMaxMom = mow->getMaxMom() * 10;
	mStats.mMinMom=mow->getMinMom();
	mStats.mRise=mow->getRiseVal() * 10;
	mStats.mFall=mow->getFallVal();
	mStats.mDurability = mow->getDurability();
	mLastDir=mow->getLastDir();
	mCurMom=mow->getCurMom();
	base = mow;
}

RoyceMower::~RoyceMower(){
	delete base;
}

intVector RoyceMower::getMove(int dir){
	/*for this decorator, we require the old momentum to know how much
	meep will drift*/
	int mLastMom = mCurMom;
	/*determine the new momentum*/
	determineMom(dir, mStats);
	/*write the standard movement into an intVector*/
	intVector stdMove = writeMove(dir);
	intVector newMove;
	/*add the standard movement after half the previous turns movement*/
	for (int i = 0; i < mLastMom; i += 2){
		newMove.push_back(mLastDir);
	}
	for (intVector::size_type i = 0; i < stdMove.size(); i++){
		newMove.push_back(stdMove.at(i));
	}
	mLastDir = dir;
	return newMove;
}

/*refer to base writeMove() and return that vector*/
intVector RoyceMower::writeMove(int dir){
	intVector mov = base->writeMove(dir);
	return mov;
}

/*refer inwards towards base mower. Then copy its current momentum*/
void RoyceMower::determineMom(int dir, mowStats stats){
	base->determineMom(dir, stats);
	mCurMom = base->getCurMom();
}

/*this function should never be called, and thus does nothing. 
A product of inheritance*/
void RoyceMower::momRise(mowStats stats){
}

/*this function should never be called, and thus does nothing.
A product of inheritance*/
void RoyceMower::momFall(mowStats stats){
}

int RoyceMower::getMaxMom() const{
	return mStats.mMaxMom;
}

int RoyceMower::getMinMom() const{
	return mStats.mMinMom;
}

int RoyceMower::getRiseVal() const{
	return mStats.mRise;
}

int RoyceMower::getFallVal() const{
	return mStats.mFall;
}

int RoyceMower::getDurability() const{
	return mStats.mDurability;
}

bool RoyceMower::getFunctioning() const{
	return mStats.mFunctioning;
}

int RoyceMower::getLastDir() const{
	return mLastDir;
}

int RoyceMower::getCurMom() const{
	return mCurMom;
}

/*int mMaxMom;
int mMinMom;
int mRise;
int mFall;
int mDurability;
bool mFunctioning=true;*/
std::string RoyceMower::getStats(){
	std::string s, nextLine;
	s = "Minimum momentum: " + mStats.mMinMom;
	nextLine = "\nMaximum momentum" + mStats.mMaxMom;
	s += nextLine;
	nextLine = "\nRise: " + mStats.mRise;
	s += nextLine;
	nextLine = "\nFall: " + mStats.mFall;
	s += nextLine;
	return nextLine;
}

void RoyceMower::resetValues(){
	mCurMom = mStats.mMinMom;
	mLastDir = 0;
}

void RoyceMower::setToMin(int dmg){
	mCurMom = mStats.mMinMom;
	mStats.mDurability -= dmg;
	if (mStats.mDurability <= 0){
		mStats.mFunctioning = false;
	}
}