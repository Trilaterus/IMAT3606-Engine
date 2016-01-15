/** \file RandomResource.cpp
The RandomResource class is designed to simply and efficiently
return random values. It uses a method which ensures random
numbers between compiles. Currently no failsafe mechanisms are
implemented.
*/

#include "RandomResource.h"

/**
The only constructor for the RandomResource class.
*/
RandomResource::RandomResource()
{

}

/**
Returns a random integer between the specified minimum
and maximum range.

\param iMin The lowest int the resource could return.
\param iMax The highest int the resource could return.
\return An int between the specified min and max values.
*/
int RandomResource::generateInt(int iMin, int iMax)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(iMin, iMax);
	return dist(mt);
}

/**
Returns a random float between the specified minimum
and maximum range.

\param fMin The lowest float the resource could return.
\param fMin The highest float the resource could return.
\return A float between the specified min and max values.
*/
float RandomResource::generateFloat(float fMin, float fMax)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(fMin, fMax);
	return dist(mt);
}

/**
Returns a boolean by randomly generating an integer
which is either 0 or 1.

\return A random boolean value.
*/
bool RandomResource::generateBool()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 2);
	if (dist(mt) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}