#include "TDCD.h"

bool tdcd::PointVPlaneTest(sf::Vector3f v3TestPoint, sf::Vector3f v3PlaneNormal, float fOffset)
{
	float fDist; // = dot product of (testPoint, planeNormal) - fOffset;
	fDist = tdcd::dotProduct(v3TestPoint, v3PlaneNormal) - fOffset;

	if (fDist > 0)
	{
		// Point is in front of plane
		// So the point is not colliding with the object
		return false;
	}
	else
	{
		// Point is behind or directly on the plane
		// So the point is colliding with the object
		return true;
	}
}

bool tdcd::PointVAABBTest(sf::Vector3f v3CubeMin, sf::Vector3f v3CubeMax, sf::Vector3f v3Point)
{
	if (v3Point.x > v3CubeMin.x && v3Point.x < v3CubeMax.x &&
		v3Point.y > v3CubeMin.y && v3Point.y < v3CubeMax.y &&
		v3Point.z > v3CubeMin.z && v3Point.z < v3CubeMax.z)
	{
		// If the point is within the min and max boundaries then it is colliding
		return true;
	}

	// If any axis is out of the boundaries then it is not colliding
	return false;
}

bool tdcd::AABBVAABBTest(sf::Vector3f v3Cube1Min, sf::Vector3f v3Cube1Max, sf::Vector3f v3Cube2Min, sf::Vector3f v3Cube2Max)
{
	if (v3Cube1Max.x > v3Cube2Min.x &&
		v3Cube1Min.x < v3Cube2Max.x &&
		v3Cube1Max.y > v3Cube2Min.y &&
		v3Cube1Min.y < v3Cube2Max.y &&
		v3Cube1Max.z > v3Cube2Min.z &&
		v3Cube1Min.z < v3Cube2Max.z)
	{
		return true;
	}

	return false;
}

bool tdcd::PointVSphereTest(sf::Vector3f v3SphereCentre, float fSphereRadius, sf::Vector3f v3TestPoint)
{
	// Calculate the squared distance from the test point to the centre of the sphere
	sf::Vector3f v3Distance;
	v3Distance = v3SphereCentre - v3TestPoint;
	float fDistSq = tdcd::dotProduct(v3Distance, v3Distance);

	// Calculate if the squared distance is less than or more than the sphere radius
	if (fDistSq < (fSphereRadius * fSphereRadius)) // This method removes the need for using the 'sqrt'n function
	{
		return true;
	}

	return false;
}

bool tdcd::SphereVSphereTest(sf::Vector3f v3Sphere1Centre, float fSphere1Radius, sf::Vector3f v3Sphere2Centre, float fSphere2Radius)
{
	// Calculate the squared distance between the centres of both spheres
	sf::Vector3f v3Distance;
	v3Distance = v3Sphere2Centre - v3Sphere1Centre;
	float fDistSq = tdcd::dotProduct(v3Distance, v3Distance);

	// Calculate the squared sum of both radii
	float fRadiiSumSq = fSphere1Radius + fSphere2Radius;
	fRadiiSumSq *= fRadiiSumSq;

	if (fDistSq <= fRadiiSumSq)
	{
		return true;
	}
	
	return false;
}

bool tdcd::SphereVPlaneTest(sf::Vector3f v3SphereCentre, float fSphereRadius, sf::Vector3f v3Point, sf::Vector3f v3Normal)
{
	sf::Vector3f v3Temp = v3SphereCentre - v3Point;

	float fDist = tdcd::dotProduct(v3Temp, v3Normal);

	if (fDist > fSphereRadius)
	{
		return false;
	}

	return true;
}

bool tdcd::RayVSphere(sf::Vector3f v3RayDir, sf::Vector3f v3RayStart, sf::Vector3f v3SphereCentre, float fSphereRadius, float& fTime)
{
	// Create vector from sphere to start of ray
	sf::Vector3f v3V1 = v3RayStart - v3SphereCentre;

	// Get dot product of this vector with ray direction
	float fB = tdcd::dotProduct(v3V1, v3RayDir);

	// Get the square distance from start of ray to sphere surface
	float fC = tdcd::dotProduct(v3V1, v3V1) - (fSphereRadius * fSphereRadius);

	// If the ray starts outside the sphere and points away from it return false here
	if (fC > 0.0f && fB > 0.0f)
	{
		return false;
	}

	// Else get discriminant for our quadratic equation
	float fDisc = fB * fB - fC;

	// If this is zero we return false
	if (fDisc < 0.0f)
	{
		return false;
	}

	// If we need the time of the collision then return the following
	// if not then we could just return true here

	fTime = -fB - sqrt(fDisc);

	// If the time is less than zero when it collided that indicates that
	// the ray started on the inside of the sphere
	if (fTime < 0.0f)
	{
		fTime = 0.0f;
	}

	return true;

	// The point of collision is:
	// sf::Vector3f v3RayLength = v3RayStart + v3RayDir * fTime;
}

bool tdcd::MovingSphereToSphere(sf::Vector3f v3MovSphereCentre, float fMovSphereRadius, sf::Vector3f v3MovSphereVel, sf::Vector3f v3StaSphereCentre, float fStaSphereRadius, float& fTime)
{
	// First create a new sphere which has the position of the static sphere but the radius of both spheres
	sf::Vector3f v3NewSphereCentre = v3StaSphereCentre;
	float fNewSphereRadius = fMovSphereRadius + fStaSphereRadius;

	// Get length of sphere's velocity to use for RayVSphere test
	float fVecLength = tdcd::getMagnitude(v3MovSphereVel);

	// Create a ray that starts at the moving sphere's centre and has the direction of the normalised velocity
	sf::Vector3f v3RayStart = v3MovSphereCentre;
	sf::Vector3f v3RayDir(v3MovSphereVel.x / fVecLength, v3MovSphereVel.y / fVecLength, v3MovSphereVel.z / fVecLength);

	// Call our RayVSphere function
	if (RayVSphere(v3RayDir, v3RayStart, v3NewSphereCentre, fNewSphereRadius, fTime))
	{
		// check if the time is less than or equal to the velocity length
		if (fTime <= fVecLength)
		{
			return true;
		}
	}
	
	return false;
}

float tdcd::dotProduct(sf::Vector3f v3A, sf::Vector3f v3B)
{
	float fValue = (v3A.x * v3B.x) + (v3A.y * v3B.y) + (v3A.z * v3B.z);
	return fValue;
}

sf::Vector3f tdcd::crossProduct(sf::Vector3f v3A, sf::Vector3f v3B)
{
	sf::Vector3f v3Vector;
	v3Vector.x = ((v3B.y * v3A.z) - (v3B.z * v3A.y));
	v3Vector.y = ((v3B.z * v3A.x) - (v3B.x * v3A.z));
	v3Vector.z = ((v3B.x * v3A.y) - (v3B.y * v3A.x));
	// Potentially normalize if doesnt work.
	return v3Vector;
}

float tdcd::getMagnitude(sf::Vector3f v3A)
{
	return sqrt((v3A.x * v3A.x) +
				(v3A.y * v3A.y) +
				(v3A.z * v3A.z));
}