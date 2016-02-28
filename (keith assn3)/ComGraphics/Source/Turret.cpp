#include "Turret.h"


Turret::Turret(const int&hp, const int&dmg, const Vector3 &pos) :damage(dmg), position(pos)
{
	Hp = hp;
	fireDelay = 0;
	shooting = 0;
	BulletSpeed = 75.0f;
	turretRotation = 0;
	hit = 0;
}

Turret::~Turret()
{
}

void Turret::LookAtEnemy(GameObject enemy)
{
	Target = enemy.position;
	Vector3 view = Target - position;
	if (Target.z > position.z){ turretRotation = Math::RadianToDegree(atan(view.x / view.z))-180.0f; }
	else{ turretRotation = Math::RadianToDegree(atan(view.x / view.z)); }
}

void Turret::ShootAtEnemy(double dt)
{
	fireDelay += dt;
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
	}
}
void Turret::TargetEnemy(Vector3 alien)
{
	Target = alien;
	if (shooting == true)
	{
		if (DoneTargeting == false)
		{
			DoneTargeting = true;
		}
	}
	else if (shooting == false)
	{
		DoneTargeting = false;
	}
}
void Turret::ReduceHp(int dmg)
{
	Hp -= dmg;
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