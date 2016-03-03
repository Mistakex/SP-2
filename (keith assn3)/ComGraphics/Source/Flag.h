/******************************************************************************/
/*!
\file	Flag.h
\author Chin Hao Ming
\par	email: 154158D@mymail.nyp.edu.sg
\brief
Captures enemy flag and flag changes to player's flag.
*/
/******************************************************************************/

#ifndef FLAG_H
#define FLAG_H
#include"Vector3.h"
#include "GameObject.h"

/******************************************************************************/
/*!
Class Flag:
\brief	Flag status and functions. It is a child of GameObject
*/
/******************************************************************************/

class Flag:public GameObject
{
public:
	Flag();
	Flag(const Vector3 &pos, const Vector3 &rangexyz);
	~Flag();
	float FlagHeightIncrease(const float &target, const double &dt); //Flag rises return new coord
	float FlagHeightDecrease(const float &target, const double &dt);
	float getMagnitude(const Vector3 &target);

	float flagheight; //Height of flag
	bool flagIsBlue = false;
private:

	float flagRotate; // rotation of flag

	bool flagRise;    //if flag is risen
	bool isEnemyflag; //Enemy or your flag
};

#endif // !FLAG_H
