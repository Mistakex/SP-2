#include "Weapon.h"

Weapon::Weapon(int dmg, int AmmoInMag, int MaxAmmoForWeap, const int &PriceOfWeap, bool AllowZoomForWeap) : Price(PriceOfWeap)
{
	Damage = dmg;
	MaxAmmo = MaxAmmoForWeap;
	AllowZoom = AllowZoomForWeap;
	AmmoInClip = AmmoInMag;
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

bool Weapon::GetAllowZoom()
{
	return AllowZoom;
}

bool Weapon::GetZoom()
{
	if (AllowZoom == true)
	{
		if (Zoom == true){ Zoom = false; }
		else if (Zoom == false){ Zoom = true; }
		return Zoom;
	}
	return false;
}

void Weapon::setUpgradeCost(int newUC)
{
	upgradeCost = newUC;
}
int Weapon::getUpgradeCost()
{
	return upgradeCost;
}