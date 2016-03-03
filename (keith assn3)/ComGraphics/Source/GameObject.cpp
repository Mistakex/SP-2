/******************************************************************************/
/*!
\file	GameObject.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Virtual parent class for objects which require collision
*/
/******************************************************************************/

#include "GameObject.h"

size_t GameObject::count = 0; // number of GameObjects existing

/******************************************************************************/
/*!
\brief
Default constructor which increases count
*/
/******************************************************************************/

GameObject::GameObject()
{
	count++;
}

/******************************************************************************/
/*!
\brief
Default destructor which decreases count
*/
/******************************************************************************/

GameObject::~GameObject()
{
	count--;
}
