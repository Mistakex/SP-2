#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	Weapon(int dmg, int AmmoInClip, int MaxAmmoForWeap, const int& price, bool AllowZoomForWeap);
	~Weapon();
	void FireAllow(double dt);						//Goes into Update
	bool GetAllowFire();							//Goes into Update
	bool GetAllowZoom();
	bool GetZoom();
	int getUpgradeCost();
	void setUpgradeCost(int newUC);

	int upgradeCost = Price;
	int Damage;
private:
	int MaxAmmo;
	int AmmoInClip;
	const int Price;

	float FireSpeed;		//cooldown for second bullet
	float FireDelay;
	bool AllowFire;
	bool AllowZoom;
	bool Zoom;
};



#endif // !WEAPON_H
