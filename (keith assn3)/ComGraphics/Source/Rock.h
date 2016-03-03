/******************************************************************************/
/*!
\file	Rock.h
\author Leong Jun Xiang
\par	email: 152907b\@mymail.nyp.edu.sg
\brief
Conatains Rock functions
*/
/******************************************************************************/
#ifndef ROCK_H
#define ROCK_H
#include "Vector3.h"
#include "GameObject.h"
/******************************************************************************/
/*!
Class Rock:
\brief	Rock stats and updates
*/
/******************************************************************************/
class Rock : public GameObject
{
public:
	Rock(Vector3 pos,float SizeOfRock);
	~Rock();
	void ReduceSize();
	int GetResources();
	float GetSize();

	int Resources;
	float Size;
private:
};


#endif // !ROCK_H