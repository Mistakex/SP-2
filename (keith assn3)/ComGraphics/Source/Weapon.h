/******************************************************************************/
/*!
\file	Weapon.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Weapon class which allows for shooting
*/
/******************************************************************************/

#ifndef WEAPON_H
#define WEAPON_H

#include "Bullet.h"
#include "Camera3.h"
#include <vector>
#include "Enemy.h"

using std::vector;

/******************************************************************************/
/*!
Class Weapon:
\brief
Weapon class which is used for shooting and damaging enemies
*/
/******************************************************************************/

class Weapon
{
public:
	Weapon();
	Weapon(const int &dmg,const int &AmmoInClip, const int &price,const bool &AllowZoomForWeap);
	~Weapon();
	void init(Camera3 *camera, vector<CollisionObject> *Pillars);
	void Fire(vector<Enemy> *aliens, Enemy *Boss);						//Goes into Update
	void FireSR(vector<Enemy> *aliens, Enemy *Boss);
	bool GetAllowZoom();
	bool GetZoom();
	int getUpgradeCost();
	void setUpgradeCost(int newUC);
	void update(double dt);
	bool checkBulletCollision(vector<Enemy> *aliens, Enemy *Boss,Bullet bullet);
	bool checkBulletCollisionSR(vector<Enemy> *aliens, Enemy *Boss,Bullet bullet);
	Bullet* Magazine;
	int upgradeCost;
	int Damage;
	const int initialDamage;
	const int initialUC;
	int AmmoInClip;
	bool hit;
private:
	float hitDelay;
	const int Price;
	int bulletCount;
	float FireDelay;
	bool AllowZoom;
	bool Zoom;
	Camera3 *camera;
	vector<CollisionObject> *Pillars;
};
#endif // !WEAPON_H
