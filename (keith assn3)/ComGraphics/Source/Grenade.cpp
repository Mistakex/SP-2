#include "Grenade.h"

Grenade::Grenade(Vector3 pos, Vector3 target, int dmg, int range,float time): throwGrenade(time)
{
	damage = dmg;
	Range = range;
	Explode = false;
	size = 0;
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
			Position += View*(float)dt*10.f;
		}
		else
		{
			Position.x += View.x*(float)dt * 10;
			Position.z += View.z*(float)dt * 10;
			if (Position.y >= -1)
			{
				Position.y -= View.y*(float)dt*10.f;
			}
		}
	}
	else if (View.y <=0)
	{
		if (Position.y >= -1)
		{
			Position.x += View.x*(float)dt *10;
			Position.z += View.z*(float)dt * 10;
			Position.y += View.y*(float)dt * 10;
		}
	}
	GrenadeRotation += 180 * (float)dt;
}
void Grenade::LookAt()
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
Grenade& Grenade::operator=(const Grenade& nade)
{
	LookAtDirection = nade.LookAtDirection;
	GrenadeRotation = nade.GrenadeRotation;
	size = nade.size;
	Explode = nade.Explode;
	Range = nade.Range;
	damage = nade.damage;
	Position = nade.Position;
	Target = nade.Target;
	View = nade.View;
	throwGrenade = nade.throwGrenade;
	return *this;
}
Vector3 Grenade::GetPosition()
{
	return Position;
}
void Grenade::GetExplosion()
{
	size += 0.11f*((float)Range / 2.f);
}
Grenade::~Grenade()
{
}
