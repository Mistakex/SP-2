/******************************************************************************/
/*!
\file	Rock.cpp
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Rock Functions
*/
/******************************************************************************/
#include "Rock.h"

/******************************************************************************/
/*!
\brief	constructor for rock

\param	pos
Position of rock
\param	SizeOfRock
Size of rock
*/
/******************************************************************************/
Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	position = pos;
	rangexyz = Vector3(SizeOfRock, SizeOfRock, SizeOfRock)*0.8f;
}
/******************************************************************************/
/*!
\brief	Returns the amount of resources

\return Resources
*/
/******************************************************************************/
int Rock::GetResources()
{
	Resources = (rand() % 5+1);
	return Resources;
}
/******************************************************************************/
/*!
\brief	Reduce the size of rock
*/
/******************************************************************************/
void Rock::ReduceSize()
{
	Size -= 0.5;
	rangexyz -= Vector3(0.5f, 0.5f, 0.5f);
}
/******************************************************************************/
/*!
\brief	returns size of the rock
\return
Size of rock
*/
/******************************************************************************/
float Rock::GetSize()
{
	return Size;
}
/******************************************************************************/
/*!
\brief	destructor for rock
*/
/******************************************************************************/
Rock::~Rock()
{
}