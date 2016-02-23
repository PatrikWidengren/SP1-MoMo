#ifndef INCLUDED_ABS_MOWER
#define INCLUDED_ABS_MOWER
#include <vector>
#include <string>

typedef std::vector<int> intVector;
struct mowStats{
	/*values for maximum- and minimum momentum, rise-value, and fall-value, respectively*/
	int mMaxMom;
	int mMinMom;
	int mRise;
	int mFall;
	const int mMaxDurability = 20;
	int mDurability;
	bool mFunctioning=true;
};

class Mower
{
public:
	Mower();
	virtual ~Mower() = 0;
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

	virtual void resetStats() = 0;

	/*setToMin() reduces mower to minimum speed in case of collision*/
	virtual void setToMin(int dmg) = 0;
	/*resetValues() is used to change the mLastDir and mCurMom so that they
	do not carry values over between games. Should be called at the start and end of
	each level, just to be sure*/
	virtual void resetValues() = 0;
	/*getNextMom() may not be used for a while, but is planned to calculate the movement value in the currently
	selected direction once that has been implemented. Basically a copy of getMoveValue() that doesn't change any values*/
	//virtual int getNextMom() const = 0;
	/*helper functions to increase and decrease momentum to make code more readable. They take a mowStats
	struct so that they can perform the same task with different values if a decorator needs it*/
	virtual void momRise(mowStats stats) = 0;
	virtual void momFall(mowStats stats) = 0;
	/*Helper functions to separate determining the changes to momentum
	and the movement. Needed for decorators to work as intended*/
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
};


#endif