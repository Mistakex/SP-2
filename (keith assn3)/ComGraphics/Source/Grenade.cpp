/******************************************************************************/
/*!
\file	Grenade.cpp
\author Leong Jun Xiang
\par	email: 152907b\@mymail.nyp.edu.sg
\brief
Grenade from flying till explosion
*/
/******************************************************************************/

#include "Grenade.h"

/******************************************************************************/
/*!
\brief	constructor for grenade class

\param	pos
Grenade position
\param	target
Grenade target
\param	dmg
Grenade damage
\param	range
Grenade explosion range
\param	time
Grenade explosion time required
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief	the grenade flying around in the sky

\param	dt
delta time value
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief	Grenade facing the correct direction
*/
/******************************************************************************/
void Grenade::LookAt()
{
	if (Target.z > Position.z)
	LookAtDirection	= Math::RadianToDegree(atan(View.x / View.z)) - 180;
	else
	LookAtDirection = Math::RadianToDegree(atan(View.x / View.z));
}
/******************************************************************************/
/*!
\brief	reduce the health of the enemy

\param enemy
Enemy object
*/
/******************************************************************************/
void Grenade::DealDamage(Enemy& enemy)
{
	if (sqrt(pow((enemy.position.x - Position.x), 2) + pow((enemy.position.z - Position.z), 2)) < Range)
	{
		enemy.EnemyTakeDmg(damage);
	}
}
/******************************************************************************/
/*!
\brief	copy the data of another grenade object

\param	nade
Grenade object
\return
Grenade object
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief	spawn alien

\return
return the position of the grenade
*/
/******************************************************************************/
Vector3 Grenade::GetPosition()
{
	return Position;
}
/******************************************************************************/
/*!
\brief	increase the size of the explosion
*/
/******************************************************************************/
void Grenade::GetExplosion()
{
	size += 0.11f*((float)Range / 2.f);
}
/******************************************************************************/
/*!
\brief	defult destructor
*/
/******************************************************************************/
Grenade::~Grenade()
{
}
