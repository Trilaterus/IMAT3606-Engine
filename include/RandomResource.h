/** \file RandomResource.h
The header file for the RandomResource class.
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

	int generateInt(int iMin, int iMax);
	float generateFloat(float fMin, float fMax);
	bool generateBool();

};

#endif //RANDOMRESOURCE_H