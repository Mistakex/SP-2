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
	Weapon(const int &dmg,const int &AmmoInClip,const int &MaxAmmoForWeap, const int& price,const bool &AllowZoomForWeap);
	~Weapon();
	void init(Camera3 *target);
	void Fire();						//Goes into Update
	bool GetAllowZoom();
	bool GetZoom();
	int getUpgradeCost();
	void setUpgradeCost(int newUC);
	void update(double dt);
	bool checkBulletCollision(vector<Enemy*> aliens,Bullet bullet);
	Bullet* Magazine;
	int upgradeCost;
	int Damage;
	int AmmoInClip;
private:
	int MaxAmmo;
	const int Price;
	int bulletCount;
	float FireDelay;
	bool AllowZoom;
	bool Zoom;
	Camera3 *camera;
};



#endif // !WEAPON_H
