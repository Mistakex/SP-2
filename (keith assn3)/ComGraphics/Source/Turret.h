#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Vector3.h"

class Turret
{
public:
	Turret(const int&hp, const int&dmg, const Vector3 &pos);
	~Turret();

	void LookAtEnemy(Enemy enemy);//Funtion to get turretRotation
	void ReduceHp(int dmg);
	void ShootAtEnemy(double dt);
	int GetDamage();
	bool GetShooting();
	void TargetEnemy(Vector3);

	Vector3 GetPosition();
	float turretRotation;		//rotates to the enemy position
	Vector3 bulletPos;
	Vector3 Target;
	bool shooting;
	bool hit;
private:
	int Hp;
	const int damage;
	const Vector3 position;
	Vector3 Alien;
	float fireDelay;
	float BulletSpeed;
	bool DoneTargeting;
};



#endif // !TURRET_H
