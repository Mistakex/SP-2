/******************************************************************************/
/*!
\file	Grenade.h
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Grenade from flying till explosion
*/
/******************************************************************************/
#ifndef GRENADE_H
#define GRENADE_H

#include "Vector3.h"
#include "CountDown.h"
#include "Enemy.h"

/******************************************************************************/
/*!
Class Grenade:
\brief	Grenade stats and updates
*/
/******************************************************************************/
class Grenade
{
public:
	Grenade(Vector3 pos , Vector3 target,int damage ,int Range,float time);
	~Grenade();
	void ThrowGrenade(double dt);
	void DealDamage(Enemy& enemy);
	void GetExplosion();
	Vector3 GetPosition();
	Countdown throwGrenade;
	Grenade& operator=(const Grenade& nade);
	void LookAt();
	float LookAtDirection;
	float GrenadeRotation;
	float size;
	bool Explode;
private:
	int Range;
	int damage;
	Vector3 Position;
	Vector3 Target;
	Vector3 View;
};



#endif // !GRENADE_H
