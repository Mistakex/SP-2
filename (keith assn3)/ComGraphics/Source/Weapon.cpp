#include "Weapon.h"

#include <iostream>

Weapon::Weapon(const int &dmg, const int &AmmoInMag, const int &MaxAmmoForWeap, const int &PriceOfWeap, const bool &AllowZoomForWeap) : Price(PriceOfWeap)
{
	Damage = dmg;
	MaxAmmo = MaxAmmoForWeap;
	AllowZoom = AllowZoomForWeap;
	AmmoInClip = AmmoInMag;
	upgradeCost = Price;
	bulletCount = 0;
	Magazine = new Bullet[AmmoInMag];
	hit = false;
	hitDelay = 0.f;
}

Weapon::~Weapon()
{
	delete[] Magazine;
}

void Weapon::init(Camera3 *camera)
{
	this->camera = camera;
}

void Weapon::Fire(vector<Enemy> aliens)
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		if (checkBulletCollision(aliens, Magazine[bulletCount]) == true)
		{
			hit = true;
		}
		bulletCount++;
	}
	else
	{
		bulletCount = 0;
	}
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
	for (int i = 0; i < AmmoInClip; ++i)
	{
		if (Magazine[i].getPosition() != Vector3(0,-10,0))
			Magazine[i].moveBullet(dt);
	}
	if (hit == true)
	{
		hitDelay += dt;
		if (hitDelay > 0.3f)
		{
			hit = false;
			hitDelay = 0.f;
		}
	}
}

bool Weapon::checkBulletCollision(vector<Enemy> aliens,Bullet bullet)
{
	for (vector<Enemy>::iterator it = aliens.begin(); it != aliens.end(); ++it)
	{
		
		Vector3 temp = bullet.getPosition();
		for (int i = 0; i < 100; ++i)
		{
			temp += bullet.getView().Normalized();
			if (temp.x >(*it).position.x - (*it).rangexyz.x && temp.x < (*it).position.x + (*it).rangexyz.x
				&& temp.y >(*it).position.y - (*it).rangexyz.y && temp.y < (*it).position.y + (*it).rangexyz.y
				&& temp.z >(*it).position.z - (*it).rangexyz.z && temp.z < (*it).position.z + (*it).rangexyz.z)
			{
				return true;
			}
		}
	}
	return false;
}