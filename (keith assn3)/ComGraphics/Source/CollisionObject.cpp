
/******************************************************************************/
/*!
\file	CollisionObject.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
For objects that require collision between the player and object.
*/
/******************************************************************************/

#include "CollisionObject.h"

/******************************************************************************/
/*!
\brief
Constructor that takes in the position of the object, the circle collision range and the xyz (cube) collision range
\param position
The position of the object
\param circle
The circle collision range of the object
\param rangexyz
The cube collision range of the object
*/
/******************************************************************************/

CollisionObject::CollisionObject(Vector3 position, float circle, Vector3 rangexyz)
{
	this->position = position;
	this->rangexyz = rangexyz;
	circleRange = circle;
}

/******************************************************************************/
/*!
\brief
Default destructor for CollisionObject
*/
/******************************************************************************/

CollisionObject::~CollisionObject()
{

}