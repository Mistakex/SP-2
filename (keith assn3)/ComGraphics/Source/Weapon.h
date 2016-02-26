#ifndef WEAPON_H
#define WEAPON_H

#include "Bullet.h"
#include "Camera3.h"
#include <vector>
#include "Enemy.h"

using std::vector;

class Weapon
{
public:
	Weapon();
	Weapon(const int &dmg,const int &AmmoInClip,const int &MaxAmmoForWeap, const int& price,const bool &AllowZoomForWeap);
	~Weapon();
	void init(Camera3 *target);
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
	int AmmoInClip;
	bool hit;
private:
	float hitDelay;
	int MaxAmmo;
	const int Price;
	int bulletCount;
	float FireDelay;
	bool AllowZoom;
	bool Zoom;
	Camera3 *camera;
};



#endif // !WEAPON_H
