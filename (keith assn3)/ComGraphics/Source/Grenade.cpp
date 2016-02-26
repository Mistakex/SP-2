#include "Grenade.h"

Grenade::Grenade(Vector3 pos, Vector3 target, const int& dmg,const int& range) :damage(dmg), Range(range)
{
	Position = pos;
	Target = target;
	View = Target - Position;
	View.Normalized();
}
void Grenade::ThrowGrenade(double dt)
{
	throwGrenade.TimeCountDown(dt);
	if (View.y > 0)
	{
		if (throwGrenade.GetTimeNow()> 2.0f)
		{
			Position += View*dt*3;
		}
		else
		{
			Position.x += View.x*dt * 3;
			Position.z += View.z*dt * 3;
			if (Position.y >= -1)
			{
				Position.y -= View.y*dt*3;
			}
		}
	}
	else if (View.y <=0)
	{
		if (Position.y >= -1)
		{
			Position.x += View.x*dt * 3;
			Position.z += View.z*dt * 3;
			Position.y += View.y*dt * 3;
		}
	}
}
void Grenade::DealDamage(Enemy& enemy)
{
	if (sqrt(pow((enemy.position.x - Position.x), 2) + pow((enemy.position.z - Position.z), 2)) < Range)
	{
		enemy.EnemyTakeDmg(damage);
	}
}
Grenade&Grenade::operator=(const Grenade& nade)
{
	Grenade a = nade;
	return a;
}
Vector3 Grenade::GetPosition()
{
	return Position;
}
Grenade::~Grenade()
{
}
