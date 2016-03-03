/******************************************************************************/
/*!
\file	Bullet.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K\@mymail.nyp.edu.sg
\brief
Bullet class for the bullets of enemies,turrets and player
*/
/******************************************************************************/

#include "Bullet.h"

/******************************************************************************/
/*!
\brief
Default constructor for bullet class, defaults the view vector and position
*/
/******************************************************************************/

Bullet::Bullet()
{
	position = Vector3(0, -10, 0);
	view = Vector3(0, 0, 0);
}

/******************************************************************************/
/*!
\brief
Default destructor for bullet class
*/
/******************************************************************************/

Bullet::~Bullet()
{

}

/******************************************************************************/
/*!
\brief
Gets the position of the bullet
\return
Returns the Vector3 position of the bullet
*/
/******************************************************************************/

Vector3 Bullet::getPosition()
{
	return position;
}

/******************************************************************************/
/*!
\brief
Gets the view vector of the bullet
\return
Returns the Vector3 view of the bullet
*/
/******************************************************************************/

Vector3 Bullet::getView()
{
	return view;
}

/******************************************************************************/
/*!
\brief
Updates the position of the bullet
\param pos
The position the bullet will be set to
*/
/******************************************************************************/

void Bullet::updatePosition(const Vector3 &pos)
{
	position = pos;
}

/******************************************************************************/
/*!
\brief
Updates the view vector of the bullet
\param view
The view vector the bullet will be set to
*/
/******************************************************************************/

void Bullet::setView(const Vector3 &view)
{
	this->view = view;
}

/******************************************************************************/
/*!
\brief
Moves the bullet based on its view vector
\exception
If the bullet travels outside of the boundaries, the view vector will be set to 0 and the bullet will stop moving
\param dt
Time in between each frame
\param speed
The speed of which the bullet will travel
*/
/******************************************************************************/

void Bullet::moveBullet(double dt,const float &speed)
{
	position += view * speed * dt;
	if (position.x > 500 || position.y > 500 || position.z > 500
		|| position.x < -500 || position.y < -500 || position.z < -500)
	{
		view = Vector3(0, 0, 0);
	}
}