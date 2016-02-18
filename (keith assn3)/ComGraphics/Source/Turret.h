#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Vector3.h"
class Turret
{
public:
	Turret(const int&hp, const int&dmg, const Vector3 &pos);
	~Turret();

	void nextTarget(Enemy enemy);//*************Might Get Subscript error if not careful.
	void ReduceHp(int dmg);
	float ShootAtEnemy(double dt);
	float turretRotation;
	Vector3 bulletPos;
	Vector3 TargetEnemy(Vector3);
private:
	int Hp;
	const int damage;
	const Vector3 position;
	Vector3 Target;
	Vector3 Alien;
	float fireDelay;
	bool shooting;
	float BulletSpeed;
	bool DoneTargeting;
};



#endif // !TURRET_H
