#ifndef INCLUDED_DECORATED_MOWER
#define INCLUDED_DECORATED_MOWER
#include "BaseMower.h"

class DecMower : public Mower
{
public:
	DecMower();
	virtual ~DecMower() = 0;
	/*getMove returns a list of steps taken,based on the direction travelled.
	These values are then used by the player to move each step in the list*/
	virtual intVector getMove(int dir) = 0;
	/*Following functions exist purely to return the encapsulated values of the members of this class
	(including struct members)*/
	virtual int getMaxMom() const = 0;
	virtual int getMinMom() const = 0;
	virtual int getRiseVal() const = 0;
	virtual int getFallVal() const = 0;
	virtual int getDurability() const = 0;
	virtual bool getFunctioning() const = 0;
	virtual int getLastDir() const = 0;
	virtual int getCurMom() const = 0;

	/*all important info into a nice readable string*/
	virtual std::string getStats() = 0;

	/*setToMin() reduces mower to minimum speed in case of collision*/
	virtual void setToMin(int dmg) = 0;
	/*resetValues() is used to change the mLastDir and mCurMom so that they
	do not carry values over between games. Should be called at the start and end of
	each level, just to be sure*/
	virtual void resetValues() = 0;
	/*getNextMom() may not be used for a while, but is planned to calculate the movement value in the currently
	selected direction once that has been implemented. Basically a copy of getMoveValue() that doesn't change any values*/
	//virtual int getNextMom() const = 0;
	/*helper functions to increase and decrease momentum to make code more readable*/
	virtual void momRise(mowStats stats) = 0;
	virtual void momFall(mowStats stats) = 0;
	/*Helper functions to separate determining the rise or fall of the momentum
	and the movement. Needed for decorator to work as intended*/
	virtual void determineMom(int dir, mowStats stats) = 0;
	virtual intVector writeMove(int dir) = 0;
protected:
	/*statblock struct for ease of use*/
	mowStats mStats;
	/*mLastDir keeps track of last direction moved with an int (on the numpad).
	That way there can be multiple kinds of lawnmowers with different movement patterns
	as they are all in charge of their own momentum. Might change int to enum later*/
	int mLastDir;
	/*mCurMom keeps track of current momentum*/
	int mCurMom;
	/*Base for decoration*/
	Mower* base;
};


#endif