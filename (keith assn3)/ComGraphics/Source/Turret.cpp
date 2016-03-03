/******************************************************************************/
/*!
\file	Turret.cpp
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Turret functions
*/
/******************************************************************************/
#include "Turret.h"

/******************************************************************************/
/*!
\brief	constructor for turret
\param	hp
health value
\param	dmg
damage value
\param	pos
position of turret
*/
/******************************************************************************/
Turret::Turret(const int&hp, const int&dmg, const Vector3 &pos) :damage(dmg), position(pos)
{
	Hp = hp;
	fireDelay = 0;
	shooting = 0;
	BulletSpeed = 25.0f;
	turretRotation = 0;
	hit = 0;
}
/******************************************************************************/
/*!
\brief	destruuctor for turret
*/
/******************************************************************************/
Turret::~Turret()
{
}
/******************************************************************************/
/*!
\brief	gets the rotation for the turret
\param	enemy
look at enemy angle
*/
/******************************************************************************/
void Turret::LookAtEnemy(GameObject enemy)
{
	Vector3 view = Target - position;
	if (Target.z > position.z){ turretRotation = Math::RadianToDegree(atan(view.x / view.z))-180.0f; }
	else{ turretRotation = Math::RadianToDegree(atan(view.x / view.z)); }
}
/******************************************************************************/
/*!
\brief	aim at enemy
\param	dt
delta time value
*/
/******************************************************************************/
void Turret::ShootAtEnemy(double dt)
{
	fireDelay += dt;
	if (fireDelay > 3.f)
	{
		fireDelay = 0.f;
		hit = true;
	}
	bullet.moveBullet(dt);
	if (fireDelay > 1 && hit == false)
	{
		if (shooting == false)
		{
			shooting = true;
			bullet.updatePosition(position - Vector3(0, 0.5, 0));
			bullet.setView((Target - position).Normalized());
		}
	}
	else if (hit == true)
	{
		hit = false;
		shooting = false;
		fireDelay = 0;
		bullet.setView(Vector3(0, 0, 0));
		bullet.updatePosition(position - Vector3(0, 0.5, 0));
	}
}
/******************************************************************************/
/*!
\brief	change target to alien
\param	alien 
alien position
*/
/******************************************************************************/
void Turret::TargetEnemy(Vector3 alien)
{
	Target = alien;
}
/******************************************************************************/
/*!
\brief	reduce the hp of the turret
\param	dmg
damage value
*/
/******************************************************************************/
void Turret::ReduceHp(int dmg)
{
	if (Hp - dmg <= 0)
	{
		Hp = 0;
	}
	else
	{
		Hp -= dmg;
	}
}
int Turret::GetDamage()
{
	return damage;
}
Vector3 Turret::GetPosition()
{
	return position;
}
bool Turret::GetShooting()
{
	return shooting;
}