#ifndef INCLUDED_GOMOWER
#define INCLUDED_GOMOWER
#include "BaseMower.h"

class GoLawnMower : public Mower
{
public:
	/*int values needed in construction of new lawnmowers.
	Unless feature creep adds crafting, there's no need to change these
	values later.*/
	GoLawnMower(int max, int min, int rise, int fall, int durability);
	GoLawnMower();
	virtual ~GoLawnMower();
	/*getMove returns a list of steps taken,based on the direction travelled.
	These values are then used by the player to move each step in the list*/
	virtual intVector getMove(int dir);
	/*Following functions exist purely to return the encapsulated values of the members of this class
	(including struct members)*/
	virtual int getMaxMom() const;
	virtual int getMinMom() const;
	virtual int getRiseVal() const;
	virtual int getFallVal() const;
	virtual int getDurability() const;
	virtual bool getFunctioning() const;
	virtual int getLastDir() const;
	virtual int getCurMom() const;

	/*all important info into a nice readable string*/
	virtual std::string getStats();

	virtual void resetStats();

	/*setToMin() reduces mower to minimum speed in case of collision*/
	virtual void setToMin(int dmg);
	/*resetValues() is used to change the mLastDir and mCurMom so that they
	do not carry values over between games. Should be called at the start and end of
	each level, just to be sure*/
	virtual void resetValues();
	/*getNextMom() may not be used for a while, but is planned to calculate the movement value in the currently
	selected direction once that has been implemented. Basically a copy of getMoveValue() that doesn't change any values*/
	//virtual int getNextMom() const = 0;
	/*helper functions to increase and decrease momentum to make code more readable. They take a mowStats
	struct so that they can perform the same task with different values if a decorator needs it*/
	virtual void momRise(mowStats stats);
	virtual void momFall(mowStats stats);
	/*Helper functions to separate determining the rise or fall of the momentum
	and the movement. Needed for decorator to work as intended*/
	virtual void determineMom(int dir, mowStats stats);
	virtual intVector writeMove(int dir);
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