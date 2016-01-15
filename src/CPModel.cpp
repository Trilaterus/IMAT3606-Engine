/** \file CPModel.cpp
The ComponentModel class associates a mesh or model with a chosen GameObject.
The mesh position, angle and colour can be modified. The mesh can also be
drawn in a way in which the camera offset does not apply to it, in effect
creating a 3D UI effect.
*/

#include "CPModel.h"

/** 
The private initalise function is called in both constructors.
It sets the default values for all of the variables that need
a set start value.
*/
void CPModel::init()
{
	clock.restart();
	m_bIsRotating = false;
	m_vfColour = { 1.0f, 1.0f, 1.0f };
	m_bCamLock = false;
	m_sModelName = "default";
}

/**
The default constructor for a CPModel. It calls the private
function init() to set some necessary variable values.

\sa init()
*/
CPModel::CPModel()
{
	init();
}

/**
This constructor allows you to choose a specific model to
load rather than the default. Model names are used in the
ModelSingleton class and are defined by the model XML file
the ModelSingleton class uses. An incorrect name will
result in the default object being drawn.
*/
CPModel::CPModel(std::string sModelName)
{
	init();

	m_sModelName = sModelName;
}

/**
The destructor for the CPModel.
*/
CPModel::~CPModel()
{

}

/**
Increments the current angle of the model by the passed float amount.
You must also specify the axis at which the rotation occurs on a scale
from 0 to 1.

\param fAngle The amount to increment the models angle.
\param fX The effect of fAngle on the X axis.
\param fY The effect of fAngle on the Y axis.
\param fZ The effect of fAngle on the Z axis.
*/
void CPModel::rotate(float fAngle, float fX, float fY, float fZ)
{
	m_vfQuaternion.x = fAngle * fX;
	m_vfQuaternion.y = fAngle * fY;
	m_vfQuaternion.z = fAngle * fZ;
}

/**
Replaces the current angle of the model with the 3 floats passed.

\param fXAngle The amount to set the X axis angle.
\param fYAngle The amount to set the Y axis angle.
\param fZAngle The amount to set the Z axis angle.
*/
void CPModel::setAngle(float fXAngle, float fYAngle, float fZAngle)
{
	m_vfAngles.x = fXAngle;
	m_vfAngles.y = fYAngle;
	m_vfAngles.z = fZAngle;
}

/**
Moves the model in the direction it is currently facing.

\param fIncrement The amount to move the model.
*/
void CPModel::move(float fIncrement)
{
	float fRadianAngle = (m_vfAngles.x * 3.14) / 180;
	m_vfPosition.z += fIncrement * cos(fRadianAngle);
	m_vfPosition.x += fIncrement * sin(fRadianAngle);
}

/**
Increments the models position based on the 3 floats passed.

\param fXChange The amount to increment the X axis.
\param fYChange The amount to increment the Y axis.
\param fZChange The amount to increment the Z axis.
*/
void CPModel::move(float fXChange, float fYChange, float fZChange)
{
	m_vfPosition.x += fXChange;
	m_vfPosition.y += fYChange;
	m_vfPosition.z += fZChange;
}

/**
Replaces the current position of the model with the 3 floats passed.

\param fXPos The new position along the X axis.
\param fYPos The new position along the Y axis.
\param fZPos The new position along the Z axis.
*/
void CPModel::setPosition(float fXPos, float fYPos, float fZPos)
{
	m_vfPosition.x = fXPos;
	m_vfPosition.y = fYPos;
	m_vfPosition.z = fZPos;
}

/**
Replaces the current colour of the model with the 3 floats passed.
This is using an RGB colour scheme on a scale from 0 to 1.

\param R The new Red value.
\param G The new Green value.
\param B The new Blue value.
*/
void CPModel::setColour(float R, float G, float B)
{
	m_vfColour = { R, G, B };
}

/**
Sets whether or not the model should be affected by the offsets
of the camera. If true the model acts like 3D UI and does not move
with the camera.

\param b A boolean defining whether or not the camera lock for the model is set
*/
void CPModel::setCamLock(bool b)
{
	m_bCamLock = b;
}


/**
Returns the current state of the models camera lock.

\return Current state of models camera lock.
*/
bool CPModel::getCamLock()
{
	return m_bCamLock;
}

/**
Update the variables of the model

\param window The window the model is being updated on.
*/
void CPModel::update(sf::RenderWindow& window)
{
	m_vfAngles += m_vfQuaternion;
}

/**
Draw the model without offsetting by the camera.
Use this function to give the illusion that the
model is being held, or that the model is part
of the UI.
*/
void CPModel::drawModel() const
{
	GLfloat colour[] = { m_vfColour.x, m_vfColour.y, m_vfColour.z };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
}

/**
Draw the model and apply the camera offset. This gives
the effect that the object is in a real world space and
the user can potentially move the camera around the model.

\param vCamAngle The angle vector to offset the model.
\param vCamPos The position vector to offset the model.
*/
void CPModel::drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const
{
	GLfloat colour[] = { m_vfColour.x, m_vfColour.y, m_vfColour.z };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!m_bCamLock)
	{
		// Camera transformations happen first
		glRotatef(vCamAngle.x, 1.f, 0.f, 0.f);
		glRotatef(vCamAngle.y, 0.f, 1.f, 0.f);
		glRotatef(vCamAngle.z, 0.f, 0.f, 1.f);
		glTranslatef(vCamPos.x, vCamPos.y, vCamPos.z);
	}
	else
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	// Then normal object transformations
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
}
