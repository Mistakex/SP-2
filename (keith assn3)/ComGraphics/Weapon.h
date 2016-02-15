#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	Weapon(int dmg, int MaxAmmoForWeap,bool AllowZoomForWeap);
	~Weapon();
	void FireAllow(double dt);						//Goes into Update
	bool GetAllowFire();							//Goes into Update
	bool GetZoom();
private:
	int Damage;
	int MaxAmmo;

	float FireSpeed;		//cooldown for second bullet
	float FireDelay;
	bool AllowFire;
	bool AllowZoom;
	bool Zoom;
};



#endif // !WEAPON_H
