/******************************************************************************/
/*!
\file	Flag.cpp
\author Chin Hao Ming
\par	email: 154158D\@mymail.nyp.edu.sg
\brief
Flag goes down while capturing. Flag changes to player's flag when successfully
captured.
*/
/******************************************************************************/
#include"Flag.h"

/******************************************************************************/
/*!
\brief
Default constructor for flag class
\param isEnemyflag
Checks whether it is enemy's flag or player's flag
*/
/******************************************************************************/

Flag::Flag() : isEnemyflag(false)
{
	flagheight = 2.5;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor for flag class
\param pos
Checks for flag position
\param rangexyz
Checks for the range of flag's x, y, z coordinates.
*/
/******************************************************************************/

Flag::Flag(const Vector3 &pos, const Vector3 &rangexyz) : isEnemyflag(false)
{
	position = pos;
	this->rangexyz = rangexyz;
	flagheight = 2.5;
}

/******************************************************************************/
/*!
\brief
Default destructor for flag class
*/
/******************************************************************************/

Flag::~Flag()
{
}

/******************************************************************************/
/*!
\brief
Getter function for magnitude of flag.
\return
Returns distance between flag and player.
*/
/******************************************************************************/

float Flag::getMagnitude(const Vector3 &target)
{
	Vector3 view = target - position;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

/******************************************************************************/
/*!
\brief
Increases the flag height to a certain y-target.
\return
Returns the flag's height.
*/
/******************************************************************************/

float Flag::FlagHeightIncrease(const float &target, const double &dt)
{
	float speed = 0.1;
	if (flagheight < target)
	{
		flagheight += speed * dt;
	}

	return flagheight;
}

/******************************************************************************/
/*!
\brief
Decreases the flag height to a certain y-target.
\return
Returns the flag's height.
*/
/******************************************************************************/

float Flag::FlagHeightDecrease(const float &target, const double &dt)
{
	float speed = 0.1;
	if (flagheight > target)
	{
		flagheight -= speed * dt;
	}
	if (flagheight <= target)
	{
		flagheight = target;
	}
	return flagheight;
}