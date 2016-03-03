/******************************************************************************/
/*!
\file	GameObject.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Virtual parent class for objects which require collision
*/
/******************************************************************************/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector3.h"
#include <vector>

using std::vector;

/******************************************************************************/
/*!
Class GameObject:
\brief	Virtual parent class for every object that requires collision detection
*/
/******************************************************************************/

class GameObject
{
public:
	virtual ~GameObject();
	Vector3 position;
	Vector3 rangexyz;
	static size_t count;
protected:
	GameObject();
};

#endif