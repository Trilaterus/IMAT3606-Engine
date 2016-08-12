/**
The ComponentLightSource class allows the GameObject that has it attached to emit
light. The lights colour, position and attentuation can be changed. To use a CPLightSource
in code you must remember to call updateAll() once to enable the light (although this is
usually done for you in the Scene class initialisation).

@author Hussain */

#ifndef CPLIGHT_H
#define CPLIGHT_H

#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>

class CPLightSource
{
private:
	int m_iGLLightID;
	sf::Vector3f m_vfAmbient;
	sf::Vector3f m_vfDiffuse;
	sf::Vector3f m_vfSpecular;
	sf::Vector3f m_vfPosition;
	bool m_bIsLightOn;

public:
	CPLightSource();

	/**
	Replaces the current LightSource position with the 3D vector passed.
	@param vfPosition The new lightsource position float vector */
	void setPosition(sf::Vector3f vfPosition);

	/**
	Replaces the current RGB ambient light value with the 3D vector passed.
	@param vfAmbient The new ambient colour vector on a scale from 0 to 1 */
	void setAmbient(sf::Vector3f vfAmbient);

	/**
	Replaces the current RGB diffuse light value with the 3D vector passed.
	@param vfDiffuse The new diffuse colour vector on a scale from 0 to 1 */
	void setDiffuse(sf::Vector3f vfDiffuse);

	/**
	Replaces the current RGB specular light value with the 3D vector passed.
	@param vfSpecular The new specular colour vector on a scale from 0 to 1 */
	void setSpecular(sf::Vector3f vfSpecular);

	/**
	Toggles the diffuse lighting on and off. */
	void toggleLight();

	/**
	Binds the associated colour values to the appropriate OpenGL functions.
	Call this function once to enable the lights, although it is usually done
	through the Scene class.
	You will need to call this function if the lights colours are changing often. */
	void updateAll();

	/**
	Updates the position of the light based on the camera.
	@param vfCameraAngle A 3D vector representing the angle offsets of the camera
	@param vfCameraPos A 3D vector representing the position offsets of the camera */
	void updatePosition(sf::Vector3f vfCameraAngle, sf::Vector3f vfCameraPos);
};

#endif