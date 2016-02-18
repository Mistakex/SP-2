#include "Turret.h"


Turret::Turret(const int&hp, const int&dmg, const Vector3 &pos) :damage(dmg),position(pos)
{
	Hp = hp;
}

Turret::~Turret()
{
}
bool Turret::TargetDead(Enemy enemy)
{
	return 0;
}
void Turret::nextTarget(Enemy enemy)
{

}
void Turret::ReduceHp(int dmg)
{
	Hp -= dmg;
}