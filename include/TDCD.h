/**
Header file containing a namespace that holds functions for various 3D Collision Detection techniques
Heavily inspired from the tutorials on the site: http://www.miguelcasillas.com/?mcportfolio=collision-detection-c

@author Hussain */

#include <SFML\System.hpp>
#include <math.h>

namespace tdcd
{
	// Tested //

	/**
	This function is used to see if a point in 3D space is colliding or behind a given plane.
	@param v3TestPoint - The point to test for collisions
	@param v3PlaneNormal - The normal of the plane that is being tested
	@param fOffset - A distance away from the plane to help reduce the chance of collision resolution issues
	@return True if the point is behind or on the plane */
	bool PointVPlaneTest(sf::Vector3f v3TestPoint, sf::Vector3f v3PlaneNormal, float fOffset); //This functions finds out if a point in 3D space is colliding with or behind a plane.
	

	/**
	This function is used to see if a point in 3D is colliding with an AABB defined using a min and max point
	@param v3CubeMin - The backward, bottom left side point of the cube
	@param v3CubeMax - The front, top right side point of the cube
	@param v3Point - The point to test for collision
	@return True if the point is within the boundaries of the AABB */
	bool PointVAABBTest(sf::Vector3f v3CubeMin, sf::Vector3f v3CubeMax, sf::Vector3f v3Point); //To check if a point is inside an AABB all we need to do is check if all the points values (x, y, z) are greater than the min values, and lower than the max values.
	

	// Untested //


	/**
	This function is used to see if two AABBs are colliding with each other
	@param v3Cube1Min - The backward, bottom left side point of the first cube
	@param v3Cube1Max - The front, top right side point of the first cube
	@param v3Cube2Min - The backward, bottom left side point of the second cube
	@param v3Cube2Max - The front, top right side point of the second cube
	@return True if the AABBs are colliding */
	bool AABBVAABBTest(sf::Vector3f v3Cube1Min, sf::Vector3f v3Cube1Max, sf::Vector3f v3Cube2Min, sf::Vector3f v3Cube2Max); //Check if an AABB is colliding with another AABB using min and max points.

	/**
	This function is used to see if a point in inside of a sphere
	@param v3SphereCentre - The centre of the sphere in 3D coordinates
	@param fSphereRadius - The radius of the sphere
	@param v3TestPoint - The point to test for collision
	@return True if the point is within the sphere */
	bool PointVSphereTest(sf::Vector3f v3SphereCentre, float fSphereRadius, sf::Vector3f v3TestPoint); //We need to find the distance of the point and the centre of the sphere and compare it against the radius.

	/**
	This function is used to see if two speheres are colliding
	@param v3Sphere1Centre - The centre of the first sphere in 3D coordinates
	@param fSphere1Radius - The radius of the first sphere
	@param v3Sphere2Centre - The centre of the second sphere in 3D coordinates
	@param fSphere2Radius - The radius of the second sphere
	@return True if the spheres are colliding */
	bool SphereVSphereTest(sf::Vector3f v3Sphere1Centre, float fSphere1Radius, sf::Vector3f v3Sphere2Centre, float fSphere2Radius); //
	
	/**
	Find out if a sphere is colliding with an infinite plane.
	@param v3SphereCentre The centre of the sphere to test in 3D coordinates
	@param fSphereRadisu The radius of the sphere
	@param v3Point The 3D coordinate position of the plane
	@param v3Normal The normal vector of the plane
	@return bool True if the sphere is colliding with the plane */
	bool SphereVPlaneTest(sf::Vector3f v3SphereCentre, float fSphereRadius, sf::Vector3f v3Point, sf::Vector3f v3Normal);
	
	/**
	Find out if a ray eventually collides with a sphere.
	@param v3RayDir The direction vector of the ray
	@param v3RayStart The 3D position coordinates of the start of the ray
	@param v3SphereCentre The 3D position coordinates of the centre of the sphere
	@param fSphereRadius The radius of the sphere
	@param fTime Returns the time at which the ray would collide with the sphere
	@return True if the ray will eventually collide with the sphere */
	bool RayVSphere(sf::Vector3f v3RayDir, sf::Vector3f v3RayStart, sf::Vector3f v3SphereCentre, float fSphereRadius, float& fTime); // Not sure if usable on its own, but applies to other collision methods
	
	/**
	Find out if a sphere will eventually collide with another sphere.
	@param v3MovSphereCentre The moving spheres 3D coordinate position
	@param fMovSphereRadius The radius of the moving sphere
	@param v3MovSphereVel The velocity of the moving sphere
	@param v3StaSphereCentre The static spheres 3D coordinate position
	@param fStaSphereRadius The radius of the static sphere
	@param fTime Returns the time at which the ray would collide with the sphere
	@return True if the sphere will eventually collide with the sphere */
	bool MovingSphereToSphere(sf::Vector3f v3MovSphereCentre, float fMovSphereRadius, sf::Vector3f v3MovSphereVel, sf::Vector3f v3StaSphereCentre, float fStaSphereRadius, float& fTime);


	// Needed Vector Functions //

	/**
	Calculate the dot product of two vectors.
	@param v3A One 3D vector to dot product
	@param v3B Another 3D vector to dot prouct
	@return The dot product of the two vectors passed */
	float dotProduct(sf::Vector3f v3A, sf::Vector3f v3B);

	/**
	Calculcate the cross product of two vectors.
	@param v3A One 3D vector to cross product
	@param v3B Another 3D vector to cross prouct
	@return The cross product of the two vectors passed */
	sf::Vector3f crossProduct(sf::Vector3f v3A, sf::Vector3f v3B);

	/**
	Calculate the magnitude of a vector.
	@param v3A A 3D vector
	@return The magnitude of the vector given */
	float getMagnitude(sf::Vector3f v3A);
}