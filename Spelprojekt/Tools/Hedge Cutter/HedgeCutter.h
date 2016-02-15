#ifndef INCLUDED_HEDGECUTTER
#define INCLUDED_HEDGECUTTER
#include "BaseShears.h"

class HedgeCutter : public Shears{
public:
	HedgeCutter(int reach, int max);
	virtual ~HedgeCutter();
	/*checks if meep does or doesn't move while holding this*/
	virtual bool stopMove();
	virtual std::string getStats();
	virtual int getReach();
	/*sends back a vector of the coordinates that must be cut*/
	virtual cutVector getCuts(int arrX, int arrY);
protected:
	/*Helper function to make the theoretically infinitely branching
	coordinates be cut as they should*/
	virtual void calcCuts(coords base, int temp);
	/*private member function to keep track of what coords get cut*/
	cutVector curCuts;
	int mReach;
	int mMaxDistance;
	coords mBaseTile;
};

#endif