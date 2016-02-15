#include "Weapon.h"

Weapon::Weapon(int dmg, int MaxAmmoForWeap, bool AllowZoomForWeap)
{
	Damage = dmg;
	MaxAmmo = MaxAmmoForWeap;
	AllowZoom = AllowZoomForWeap;
}

Weapon::~Weapon()
{
}

void Weapon::FireAllow(double dt)
{
	if (AllowFire == false)
	{
		if (FireDelay < 0)
		{
			FireDelay = FireSpeed;
			AllowFire = true;
		}

	}
	else
	{
		if (FireDelay>0)
		{
			FireDelay -= dt;
		}
		else
		{
			AllowFire = false;
		}
	}
}
bool Weapon::GetAllowFire()
{
	return AllowFire;
}
bool Weapon::GetZoom()
{
	if (AllowZoom == true)
	{
		if (Zoom == true){ Zoom = false; }
		else if (Zoom == false){ Zoom = true; }
	}
}