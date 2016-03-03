/******************************************************************************/
/*!
\file	Turret.h
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Turret stats and updates
*/
/******************************************************************************/
#ifndef TURRET_H
#define TURRET_H

#include "Vector3.h"
#include "GameObject.h"
#include "Bullet.h"
/******************************************************************************/
/*!
Class Turret:
\brief	Turret updates
*/
/******************************************************************************/
class Turret
{
public:
	Turret(const int&hp, const int&dmg, const Vector3 &pos);
	~Turret();

	void LookAtEnemy(GameObject enemy);//Funtion to get turretRotation
	void ReduceHp(int dmg);
	void ShootAtEnemy(double dt);
	int GetDamage();
	bool GetShooting();
	void TargetEnemy(Vector3);

	Vector3 GetPosition();
	float turretRotation;		//rotates to the enemy position
	Bullet bullet;
	Vector3 Target;
	bool shooting;
	bool hit;
	int Hp;
	float BulletSpeed;
private:
	
	int damage;
	Vector3 position;
	Vector3 Alien;
	float fireDelay;
};



#endif // !TURRET_H
