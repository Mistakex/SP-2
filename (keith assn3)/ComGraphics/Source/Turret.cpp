#include "Turret.h"


Turret::Turret(const int&hp, const int&dmg, const Vector3 &pos) :damage(dmg),position(pos)
{
	Hp = hp;
	fireDelay = 0;
	shooting = 0;
}

Turret::~Turret()
{
}
void Turret::nextTarget(Enemy enemy)
{
	Target = enemy.EnemyPos;
	Vector3 view = Target - enemy.EnemyPos;
	if (Target.z > enemy.EnemyPos.z){turretRotation = Math::RadianToDegree(atan(view.x / view.z)) - 180;}
	else{ turretRotation = Math::RadianToDegree(atan(view.x / view.z)); }
}
void Turret::ShootAtEnemy(double dt)
{
	fireDelay += dt;
	if (fireDelay < 3)
	{
		if (shooting == true)
		{
			bulletPos += (Target - position)*BulletSpeed*dt;
		}
		else
		{
			shooting = true;
			bulletPos = position;
			Target = Alien;
		}
	}
	else
	{
		shooting = false;
		fireDelay = 0;
	}
}
Vector3 Turret::TargetEnemy(Vector3 alien)
{
	if (shooting == true)
	{
		if (DoneTargeting == false)
		{
			Alien = alien;
			DoneTargeting = true;
			return Alien;
		}
	}
	else if (shooting == false)
	{
		DoneTargeting == false;
	}
	return alien;

}
void Turret::ReduceHp(int dmg)
{
	Hp -= dmg;
}