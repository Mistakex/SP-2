#include "Grenade.h"

Grenade::Grenade(Vector3 pos, Vector3 target, const int& dmg,const int& range) :damage(dmg), Range(range)
{
	GrenadeRotation = 0;
	Position = pos;
	Target = target;
	View = Target - Position;
	View.Normalized();
	LookAt();
}
void Grenade::ThrowGrenade(double dt)
{
	throwGrenade.TimeCountDown(dt);
	if (View.y > 0)
	{
		if (throwGrenade.GetTimeNow()> 2.0f)
		{
			Position += View*dt*10;
		}
		else
		{
			Position.x += View.x*dt * 10;
			Position.z += View.z*dt * 10;
			if (Position.y >= -1)
			{
				Position.y -= View.y*dt*10;
			}
		}
	}
	else if (View.y <=0)
	{
		if (Position.y >= -1)
		{
			Position.x += View.x*dt *10;
			Position.z += View.z*dt *10;
			Position.y += View.y*dt *10;
		}
	}
	GrenadeRotation+=180*dt;
}
float Grenade::LookAt()
{
	if (Target.z > Position.z)
	LookAtDirection	= Math::RadianToDegree(atan(View.x / View.z)) - 180;
	else
	LookAtDirection = Math::RadianToDegree(atan(View.x / View.z));
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
