/**
The RandomResource class is designed to simply and efficiently
return random values. It uses a method which ensures random
numbers between compiles.
TODO: Generate functions need parameter checking.
*/

#ifndef RANDOMRESOURCE_H
#define RANDOMRESOURCE_H

#include <random>

class RandomResource
{
private:

protected:

public:
	RandomResource();

	/**
	Returns a random integer between the specified minimum
	and maximum range.
	@param iMin The lowest int the resource could return
	@param iMax The highest int the resource could return
	@return An int between the specified min and max values */
	int generateInt(int iMin, int iMax);

	/**
	Returns a random float between the specified minimum
	and maximum range.
	@param fMin The lowest float the resource could return
	@param fMin The highest float the resource could return
	@return A float between the specified min and max values */
	float generateFloat(float fMin, float fMax);

	/**
	Returns a boolean by randomly generating an integer
	which is either 0 or 1.
	@return A random boolean value */
	bool generateBool();
};

#endif //RANDOMRESOURCE_H