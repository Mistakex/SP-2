/******************************************************************************/
/*!
\file	Bullet.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Bullet class for the bullets of enemies,turrets and player
*/
/******************************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class Bullet:
\brief
Bullet class which holds the position of the bullet, the view vector of the bullet and the functions to make the bullet move
*/
/******************************************************************************/

class Bullet
{
public:
	Bullet();
	~Bullet();
	Vector3 getPosition();
	Vector3 getView();
	void updatePosition(const Vector3 &pos);
	void setView(const Vector3 &view);
	void moveBullet(double dt,const float &speed = 100);
private:
	Vector3 position;
	Vector3 view;
};


#endif