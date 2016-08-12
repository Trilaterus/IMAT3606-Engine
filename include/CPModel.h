/**
The ComponentModel class associates a mesh or model with a chosen GameObject.
The mesh position, angle and colour can be modified. The mesh can also be
drawn in a way in which the camera offset does not apply to it, essentially
creating a 3D UI effect.

@author Hussain */

#ifndef CPMODEL_H
#define CPMODEL_H

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "ModelSingleton.h"

class CPModel
{
private:
	sf::Clock clock;
	sf::Vector3f m_vfPosition;
	sf::Vector3f m_vfAngles;
	GLuint m_iTexture;
	bool m_bIsRotating;
	sf::Vector3f m_vfQuaternion;
	std::string m_sModelName;
	sf::Vector3f m_vfColour;
	bool m_bCamLock; // Will not move with camera (appear to be holding item/3D UI);

	/**
	The private initalise function is called in all constructors.
	It sets the default values for all of the variables that need
	a set start value. */
	void init();

public:
	/**
	The default constructor for a CPModel. It calls the private
	function init() to set some necessary variable values.
	@sa init() */
	CPModel();

	/**
	This constructor allows you to choose a specific model to
	load rather than the default. Model names are used in the
	ModelSingleton class and are defined by the model XML file
	the ModelSingleton class uses. An incorrect name will
	result in the default object being drawn.
	@param sModelName A string representing the model name in the XML file to render
	@sa init() */
	CPModel(std::string sModelName);

	/**
	The destructor for the CPModel. */
	~CPModel();


	/**
	Increments the current angle of the model by the passed float amount.
	You must also specify the axis at which the rotation occurs on a scale
	from 0 to 1.
	@param fAngle The amount to increment the models angle.
	@param fX The effect of fAngle on the X axis
	@param fY The effect of fAngle on the Y axis
	@param fZ The effect of fAngle on the Z axis */
	void rotate(float fAngle, float fX, float fY, float fZ); 

	/**
	Replaces the current angle of the model with the 3 floats passed.
	@param fXAngle The amount to set the X axis angle 
	@param fYAngle The amount to set the Y axis angle 
	@param fZAngle The amount to set the Z axis angle */
	void setAngle(float fXAngle, float fYAngle, float fZAngle);

	/**
	Moves the model in the direction it is currently facing.
	@param fIncrement The amount to move the model */
	void move(float fIncrement);

	/**
	Increments the models position based on the 3 floats passed.
	@param fXChange The amount to increment the X axis 
	@param fYChange The amount to increment the Y axis 
	@param fZChange The amount to increment the Z axis */
	void move(float fXChange, float fYChange, float fZChange);

	/**
	Replaces the current position of the model with the 3 floats passed.
	@param fXPos The new position along the X axis 
	@param fYPos The new position along the Y axis 
	@param fZPos The new position along the Z axis */
	void setPosition(float fXPos, float fYPos, float fZPos);

	/**
	Replaces the current colour of the model with the 3 floats passed.
	This is using an RGB colour scheme on a scale from 0 to 1.
	@param R The new Red value
	@param G The new Green value
	@param B The new Blue value */
	void setColour(float fR, float fG, float fB);

	/**
	Sets whether or not the model should be affected by the offsets
	of the camera. If true the model acts like 3D UI and does not move
	with the camera.
	@param b A boolean defining whether or not the camera lock for the model is set */
	void setCamLock(bool b);

	/**
	Returns the current state of the models camera lock.
	@return Current state of models camera lock */
	bool getCamLock();

	/**
	Returns the current position of this model.
	@return Current position of the model */
	sf::Vector3f getPosition();

	/**
	Update the variables of the model
	@param window The window the model is being updated on */
	void update(sf::RenderWindow& window);

	/**
	Draw the model without offsetting by the camera.
	Use this function to give the illusion that the
	model is being held, or that the model is part
	of the UI. */
	void drawModel() const;

	/**
	Draw the model and apply the camera offset. This gives
	the effect that the object is in a real world space and
	the user can potentially move the camera around the model.
	@param vCamAngle The angle vector to offset the model
	@param vCamPos The position vector to offset the model */
	void drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const;
};

#endif