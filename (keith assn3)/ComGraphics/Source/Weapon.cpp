#include "Weapon.h"

#include <iostream>

Weapon::Weapon(const int &dmg, const int &AmmoInMag, const int &MaxAmmoForWeap, const int &PriceOfWeap, const bool &AllowZoomForWeap) : Price(PriceOfWeap), initialDamage(dmg)
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

void Weapon::init(Camera3 *camera, vector<CollisionObject> *Pillars)
{
	this->camera = camera;
	this->Pillars = Pillars;
}

void Weapon::Fire(vector<Enemy> *aliens,Enemy *Boss)
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		if (checkBulletCollision(aliens,Boss, Magazine[bulletCount]) == true)
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
void Weapon::FireSR(vector<Enemy> *aliens,Enemy *Boss)
{
	if (bulletCount < AmmoInClip)
	{
		Magazine[bulletCount].updatePosition(camera->target);
		Magazine[bulletCount].setView(camera->view);
		if (checkBulletCollisionSR(aliens,Boss, Magazine[bulletCount]) == true)
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
		if (hitDelay > 0.2f)
		{
			hit = false;
			hitDelay = 0.f;
		}
	}
}

bool Weapon::checkBulletCollision(vector<Enemy> *aliens, Enemy *Boss, Bullet bullet)
{
		Vector3 temp = bullet.getPosition();
		for (int i = 0; i < 50; ++i)
		{
			temp += bullet.getView().Normalized();
			for (vector<CollisionObject>::iterator it2 = (*Pillars).begin(); it2 != (*Pillars).end(); ++it2)
			{
				if ((temp - it2->position).Length() < it2->circleRange)
				{
					return false;
				}
			}

			if (temp.x >(*Boss).position.x - (*Boss).rangexyz.x && temp.x < (*Boss).position.x + (*Boss).rangexyz.x
				&& temp.y >(*Boss).position.y && temp.y < (*Boss).position.y + (*Boss).rangexyz.y
				&& temp.z >(*Boss).position.z - (*Boss).rangexyz.z && temp.z < (*Boss).position.z + (*Boss).rangexyz.z
				&& Boss->bossIsSpawned && Boss->GetEnemyHp() > 0)
			{
				(*Boss).EnemyTakeDmg(Damage);
				(*Boss).redAlien = true;
				return true;
			}

			for (vector<Enemy>::iterator it = aliens->begin(); it != aliens->end(); ++it)
			{
				if (temp.x >(*it).position.x - (*it).rangexyz.x && temp.x < (*it).position.x + (*it).rangexyz.x
					&& temp.y >(*it).position.y - (*it).rangexyz.y && temp.y < (*it).position.y + (*it).rangexyz.y
					&& temp.z >(*it).position.z - (*it).rangexyz.z && temp.z < (*it).position.z + (*it).rangexyz.z)
				{
					(*it).EnemyTakeDmg(Damage);
					(*it).redAlien = true;
					return true;
				}
			}
	}
	return false;
}
bool Weapon::checkBulletCollisionSR(vector<Enemy> *aliens, Enemy *Boss, Bullet bullet)
{
	bool hitenemy = 0;
	bool hitboss = 0;

	Vector3 temp = bullet.getPosition();
	for (int i = 0; i < 100; ++i)
	{
		temp += bullet.getView().Normalized();
		for (vector<CollisionObject>::iterator it2 = (*Pillars).begin(); it2 != (*Pillars).end(); ++it2)
		{
			if ((temp - it2->position).Length() < it2->circleRange)
			{
				return false;
			}
		}
		if (temp.x >(*Boss).position.x - (*Boss).rangexyz.x && temp.x < (*Boss).position.x + (*Boss).rangexyz.x
			&& temp.y >(*Boss).position.y && temp.y < (*Boss).position.y + (*Boss).rangexyz.y
			&& temp.z >(*Boss).position.z - (*Boss).rangexyz.z && temp.z < (*Boss).position.z + (*Boss).rangexyz.z
			&& Boss->bossIsSpawned && Boss->GetEnemyHp() > 0)
		{
			hitboss = 1;
			(*Boss).redAlien = true;
		}
		for (vector<Enemy>::iterator it = aliens->begin(); it != aliens->end(); ++it)
		{
			if (temp.x >(*it).position.x - (*it).rangexyz.x && temp.x < (*it).position.x + (*it).rangexyz.x
				&& temp.y >(*it).position.y - (*it).rangexyz.y && temp.y < (*it).position.y + (*it).rangexyz.y
				&& temp.z >(*it).position.z - (*it).rangexyz.z && temp.z < (*it).position.z + (*it).rangexyz.z)
			{
				(*it).EnemyTakeDmg(Damage);
				(*it).redAlien = true;
				hitenemy = 1;
				break;
			}
		}
	}
	if (hitboss == 1)
	{
		(*Boss).EnemyTakeDmg(Damage);
		return hitboss;
	}
	return hitenemy;
}
