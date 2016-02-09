#ifndef INCLUDED_ABS_SHEARS
#define INCLUDED_ABS_SHEARS
#include <vector>
#include <array>
#include <algorithm>

typedef std::array<int, 2> coords;
typedef std::vector<coords> cutVector;

/**********************][TODO][**********************
*	Cutting range									*
*		Option for cutting everything within		*
*			range, or only cutting in straight		*
*			and/or diagonal lines					*
*	Function to determine whether or not Meep can	*
*		keep moving or if Meep stays still for		*
*		the turn. (return bool?)					*
*	Function to actually trim the hedges (once		*
*		hedges have been implemented)				*
*													*
*****************************************************/

class Shears{
public:
	Shears();
	virtual ~Shears() = 0;
	virtual bool stopMove() = 0;
	virtual int getReach() = 0;
	virtual cutVector getCuts() = 0;
protected:
	virtual void calcCuts(coords base, int temp) = 0;
};

#endif