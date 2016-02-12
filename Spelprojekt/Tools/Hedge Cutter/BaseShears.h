#ifndef INCLUDED_ABS_SHEARS
#define INCLUDED_ABS_SHEARS
#include <vector>
#include <array>
#include <algorithm>

typedef std::array<int, 2> coords;
typedef std::vector<coords> cutVector;

/**********************][TODO][**********************
*	Function to determine whether or not Meep can	*
*		keep moving or if Meep stays still for		*
*		the turn. (return bool?)					*
*													*
*****************************************************/

/************][CONSTRUCTOR INSTRUCTIONS][************
*	The contructor will take two values:			*
*		its reach, ie the amount of steps it can	*
*		cut, and its maximum reach, how many tiles	*
*		away from Meep it can cut.					*
*	Because the almighty Elvis wants it to not		*
*		not always cut diagonals, and because I do	*
*		not want to make multiple base classes,		*
*		I made special function for cutting.		*
*		Long story short, for each step it can		*
*		reach, it will step in every direction, and	*
*		in every direction from those tiles, until	*
*		it has completely run out of steps it can	*
*		reach. Then it ignores all duplicates, and	*
*		those tiles that are outside it's max reach	*
*		(ie, x or y value differ by that amount or	*
*		more), and returns the coordinates it can	*
*		cut.										*
*													*
*	TL;DR: it only reaches as far out as the max	*
*	reach. It will only check as many "steps" away	*
*	from meep in all directions as its reach		*
*****************************************************/

class Shears{
public:
	Shears();
	virtual ~Shears() = 0;
	virtual bool stopMove() = 0;
	virtual int getReach() = 0;
	virtual cutVector getCuts(int arrX, int arrY) = 0;
protected:
	virtual void calcCuts(coords base, int temp) = 0;
};

#endif