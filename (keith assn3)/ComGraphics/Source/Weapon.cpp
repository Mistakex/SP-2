/******************************************************************************/
/*!
\file	Weapon.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K\@mymail.nyp.edu.sg
\brief
Weapon class which allows for shooting
*/
/******************************************************************************/

#include "Weapon.h"

#include <iostream>

/******************************************************************************/
/*!
\brief
Constructor for weapon which takes in its stats and intializes its values
\param dmg
Damage of the gun
\param AmmoInMag
How many bullets in each magazine
\param PriceOfWeap
The price of the weapon
\param AllowZoomForWeap
To check whether the weapon allows for zooming
*/
/******************************************************************************/

Weapon::Weapon(const int &dmg, const int &AmmoInMag, const int &PriceOfWeap, const bool &AllowZoomForWeap) : Price(PriceOfWeap), initialDamage(dmg), initialUC(PriceOfWeap)
{
	Damage = dmg;
	AllowZoom = AllowZoomForWeap;
	AmmoInClip = AmmoInMag;
	upgradeCost = Price;
	bulletCount = 0;
	Magazine = new Bullet[AmmoInMag];
	hit = false;
	hitDelay = 0.f;
}

/******************************************************************************/
/*!
\brief
Destructor which deletes the Magazine of the weapon
*/
/******************************************************************************/

Weapon::~Weapon()
{
	delete[] Magazine;
}

/******************************************************************************/
/*!
\brief
Loads the camera and pillars into the weapon to check for collision
\param *camera
Loads the camera into the weapon
\param *Pillars
Loads the pillars into the weapon
*/
/******************************************************************************/

void Weapon::init(Camera3 *camera, vector<CollisionObject> *Pillars)
{
	this->camera = camera;
	this->Pillars = Pillars;
}

/******************************************************************************/
/*!
\brief
Fires the weapon,shoots the bullet and checks for collision with enemy
\param *aliens
Checks for collision with aliens
\param *Boss
Checks for collision with the Boss
*/
/******************************************************************************/

void Weapon::Fire(vector<Enemy> *aliens,Enemy *Boss)
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		if (checkBulletCollision(aliens,Boss, Magazine[bulletCount]) == true)
		{
			hit = true;
		}
		bulletCount++;
		if (bulletCount == AmmoInClip)
		{
			bulletCount = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief
Fires the sniper rifle,shoots the bullet and checks for collision with enemy (uses a piercing collision check)
\param *aliens
Checks for collision with aliens
\param *Boss
Checks for collision with the Boss
*/
/******************************************************************************/

void Weapon::FireSR(vector<Enemy> *aliens,Enemy *Boss)
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		if (checkBulletCollisionSR(aliens,Boss, Magazine[bulletCount]) == true)
		{
			hit = true;
		}
		bulletCount++;
		if (bulletCount == AmmoInClip)
		{
			bulletCount = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief
Getter function to get whether or not the weapon allows for zooming
\return
Returns true if it allows for zooming and false if not
*/
/******************************************************************************/

bool Weapon::GetAllowZoom()
{
	return AllowZoom;
}

/******************************************************************************/
/*!
\brief
Getter function to get whether or not the weapon is zoomed currently
\return
Returns true if it is zoomed and false if not
*/
/******************************************************************************/

bool Weapon::GetZoom()
{
	if (AllowZoom == true)
	{
		if (Zoom == true){ Zoom = false; }
		else if (Zoom == false){ Zoom = true; }
		return Zoom;
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Sets the new upgrade cost of the weapon (done by Zhi Yuan)
\param newUC
Sets the new upgrade cost as newUC
*/
/******************************************************************************/

void Weapon::setUpgradeCost(int newUC)
{
	upgradeCost = newUC;
}

/******************************************************************************/
/*!
\brief
Getter functions for the upgrade cost of the weapon
\return
Returns the upgrade cost of the weapon
*/
/******************************************************************************/

int Weapon::getUpgradeCost()
{
	return upgradeCost;
}

/******************************************************************************/
/*!
\brief
Updates the weapon. Moves the bullets and adds to the delay of each shot
\param dt
The time in between each frame
*/
/******************************************************************************/

void Weapon::update(double dt)
{
	for (int i = 0; i < AmmoInClip; ++i)
	{
		if (Magazine[i].getPosition() != Vector3(0,-10,0))
			Magazine[i].moveBullet(dt);
	}
	if (hit == true)
	{
		hitDelay += dt;
		if (hitDelay > 0.2f)
		{
			hit = false;
			hitDelay = 0.f;
		}
	}
}

/******************************************************************************/
/*!
\brief
Checks for collision between the bullet and the enemy and update their hp using raycasting.
\param *aliens
The vector containing every alien to check for collision
\param *Boss
Used to check for collision with boss
\param bullet
To check whether that specific bullet will collide with the aliens
\return
Returns true if there is collision and false if there is no collision
*/
/******************************************************************************/

bool Weapon::checkBulletCollision(vector<Enemy> *aliens, Enemy *Boss, Bullet bullet)
{
		Vector3 temp = bullet.getPosition();
		for (int i = 0; i < 50; ++i)
		{
			temp += bullet.getView().Normalized();
			for (vector<CollisionObject>::iterator it2 = (*Pillars).begin(); it2 != (*Pillars).end(); ++it2)
			{
				if ((temp - it2->position).Length() < it2->circleRange)
				{
					return false;
				}
			}

			if (temp.x >(*Boss).position.x - (*Boss).rangexyz.x && temp.x < (*Boss).position.x + (*Boss).rangexyz.x
				&& temp.y >(*Boss).position.y && temp.y < (*Boss).position.y + (*Boss).rangexyz.y
				&& temp.z >(*Boss).position.z - (*Boss).rangexyz.z && temp.z < (*Boss).position.z + (*Boss).rangexyz.z
				&& Boss->bossIsSpawned && Boss->GetEnemyHp() > 0)
			{
				(*Boss).EnemyTakeDmg(Damage);
				return true;
			}

			for (vector<Enemy>::iterator it = aliens->begin(); it != aliens->end(); ++it)
			{
				if (temp.x >(*it).position.x - (*it).rangexyz.x && temp.x < (*it).position.x + (*it).rangexyz.x
					&& temp.y >(*it).position.y - (*it).rangexyz.y && temp.y < (*it).position.y + (*it).rangexyz.y
					&& temp.z >(*it).position.z - (*it).rangexyz.z && temp.z < (*it).position.z + (*it).rangexyz.z)
				{
					(*it).EnemyTakeDmg(Damage);
					return true;
				}
			}
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Checks for collision between the bullet and the enemy and update their hp using raycasting (pierces through).
\param *aliens
The vector containing every alien to check for collision
\param *Boss
Used to check for collision with boss
\param bullet
To check whether that specific bullet will collide with the aliens
\return
Returns true if there is collision and false if there is no collision
*/
/******************************************************************************/

bool Weapon::checkBulletCollisionSR(vector<Enemy> *aliens, Enemy *Boss, Bullet bullet)
{
	bool hitenemy = 0;
	bool hitboss = 0;

	Vector3 temp = bullet.getPosition();
	for (int i = 0; i < 100; ++i)
	{
		temp += bullet.getView().Normalized();
		for (vector<CollisionObject>::iterator it2 = (*Pillars).begin(); it2 != (*Pillars).end(); ++it2)
		{
			if ((temp - it2->position).Length() < it2->circleRange)
			{
				return false;
			}
		}
		if (temp.x >(*Boss).position.x - (*Boss).rangexyz.x && temp.x < (*Boss).position.x + (*Boss).rangexyz.x
			&& temp.y >(*Boss).position.y && temp.y < (*Boss).position.y + (*Boss).rangexyz.y
			&& temp.z >(*Boss).position.z - (*Boss).rangexyz.z && temp.z < (*Boss).position.z + (*Boss).rangexyz.z
			&& Boss->bossIsSpawned && Boss->GetEnemyHp() > 0)
		{
			hitboss = 1;
			(*Boss).redAlien = true;
		}
		for (vector<Enemy>::iterator it = aliens->begin(); it != aliens->end(); ++it)
		{
			if (temp.x >(*it).position.x - (*it).rangexyz.x && temp.x < (*it).position.x + (*it).rangexyz.x
				&& temp.y >(*it).position.y - (*it).rangexyz.y && temp.y < (*it).position.y + (*it).rangexyz.y
				&& temp.z >(*it).position.z - (*it).rangexyz.z && temp.z < (*it).position.z + (*it).rangexyz.z)
			{
				(*it).EnemyTakeDmg(Damage);
				(*it).redAlien = true;
				hitenemy = 1;
				break;
			}
		}
	}
	if (hitboss == 1)
	{
		(*Boss).EnemyTakeDmg(Damage);
		return hitboss;
	}
	return hitenemy;
}
