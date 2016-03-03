/******************************************************************************/
/*!
\file	Harvestors.cpp
\author Leong Jun Xiang
\par	email: 152907b\@mymail.nyp.edu.sg
\brief
Harvestor functions
*/
/******************************************************************************/
#include "Harvestors.h"
/******************************************************************************/
/*!
\brief	constructor for Haervestors class

\param	pos
Harvestors position
\param	movespd
Movespeed for the Harvestors
*/
/******************************************************************************/
Harvestors::Harvestors(Vector3 pos, const float &movespd) :MoveSpeed(movespd)
{
	Position = pos;
}
/******************************************************************************/
/*!
\brief	Move towards to the rock
\param pos
Position of rock
\param	dt
delta time value
*/
/******************************************************************************/
void Harvestors::MoveTowards(Vector3 pos, double dt)
{
	Target = pos;
	view = Target - Position;
	if (pow(Target.x - Position.x, 2) + pow(Target.z - Position.z, 2) > 2)
	{	
		view.Normalized();
		Position += view*MoveSpeed*(float)dt;
	}
}
/******************************************************************************/
/*!
\brief	Reduce size of rock and obtain resources
\param rock
rock object
\param	a
player object
*/
/******************************************************************************/
void Harvestors::MineRocks(Rock& rock,Player& a)
{
	rock.ReduceSize();
	a.ObtainResources(rock.GetResources());
}
/******************************************************************************/
/*!
\brief	face direction of the rock
*/
/******************************************************************************/
void Harvestors::FindDirection()
{
	view = Target - Position;
	if (Target.z > Position.z)
		Rotation = Math::RadianToDegree(atan(view.x / view.z)) - 180;
	else
		Rotation = Math::RadianToDegree(atan(view.x / view.z));
}
/******************************************************************************/
/*!
\brief	Reduce size of rock and obtain resources
\return
rotation of the harvestor
*/
/******************************************************************************/
float Harvestors::GetHarvestorRotation()
{
	return Rotation;
}
/******************************************************************************/
/*!
\brief	defult destructor
*/
/******************************************************************************/
Harvestors::~Harvestors()
{
}
