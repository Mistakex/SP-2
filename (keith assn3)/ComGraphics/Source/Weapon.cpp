#include "Weapon.h"

Weapon::Weapon(const int &dmg, const int &AmmoInMag, const int &MaxAmmoForWeap, const int &PriceOfWeap, const bool &AllowZoomForWeap) : Price(PriceOfWeap)
{
	Damage = dmg;
	MaxAmmo = MaxAmmoForWeap;
	AllowZoom = AllowZoomForWeap;
	AmmoInClip = AmmoInMag;
	upgradeCost = Price;
	Magazine = new Bullet[AmmoInMag];
}

Weapon::~Weapon()
{
	delete[] Magazine;
}

void Weapon::Fire(double dt)
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