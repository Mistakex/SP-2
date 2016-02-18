#include "Turret.h"


Turret::Turret(const int&hp, const int&dmg, const Vector3 &pos) :damage(dmg),position(pos)
{
	Hp = hp;
}

Turret::~Turret()
{
}
void Turret::nextTarget(Enemy enemy,Enemy nextEnemy)
{
	if (enemy.isDead() == true)
	{
		Target = nextEnemy.EnemyPos;
		Vector3 view = Target - nextEnemy.EnemyPos;
		if (Target.z > nextEnemy.EnemyPos.z){Math::RadianToDegree(atan(view.x / view.z)) - 180;}
		else{Math::RadianToDegree(atan(view.x / view.z));}
	}
}
void Turret::ReduceHp(int dmg)
{
	Hp -= dmg;
}