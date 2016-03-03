#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

/******************************************************************************/
/*!
\file	CollisionObject.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
For objects that require collision between the player and object.
*/
/******************************************************************************/

#include "GameObject.h"
#include "Vector3.h"

/******************************************************************************/
/*!
Class CollisionObject:
\brief	Range and position of the CollisionObject. It is a child of GameObject
*/
/******************************************************************************/

class CollisionObject : public GameObject
{
public:
	CollisionObject(Vector3 position, float circle, Vector3 rangexyz = Vector3(1,1,1));
	~CollisionObject();
	float circleRange;
};


#endif