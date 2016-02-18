#include "Weapon.h"

Weapon::Weapon(const int &dmg, const int &AmmoInMag, const int &MaxAmmoForWeap, const int &PriceOfWeap, const bool &AllowZoomForWeap) : Price(PriceOfWeap)
{
	Damage = dmg;
	MaxAmmo = MaxAmmoForWeap;
	AllowZoom = AllowZoomForWeap;
	AmmoInClip = AmmoInMag;
	upgradeCost = Price;
	bulletCount = 0;
	Magazine = new Bullet[AmmoInMag];
}

Weapon::~Weapon()
{
	delete[] Magazine;
}

void Weapon::init(Camera3 *camera)
{
	this->camera = camera;
}

void Weapon::Fire()
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		bulletCount++;
	}
	else
	{
		bulletCount = 0;
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

void Weapon::update(double dt)
{
	for (int i = 0; i < sizeof(Magazine); ++i)
	{
		if (Magazine[i].getPosition() != Vector3(0,-10,0))
			Magazine[i].moveBullet(dt);
	}
}