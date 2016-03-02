#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Vector3.h"
#include "Weapon.h"
#include "Player.h"
#include "Harvestors.h"
#include "Medkit.h"
#include <string.h>

using std::string;

class Astronaut
{
public:
	Astronaut(Vector3 pos);
	~Astronaut();
	Vector3 GetAstronautPos();
	void AstronautMoveAround();						//The astronaut move around the spaceship in a random amount of steps

	// Upgrade Functions and variables
	void UpgradeWeapon(Weapon& weap, Player& p);							//int Damage is from Weapon class		
	void UpgradeTurret(Player& p);

	bool upgradeSuccess = false;
	int TurretNewDmg = 20; // also functions as upgrade cost

	// Purchase Functions and variables
	void PurchaseHarvestor(Player& p);

	//grenade
	void PurchaseGrenades(Player& p);
	void UpgradeGrenadeDamage(Player& p);
	void UpgradeGrenadeRange(Player& p);
	int GrenadeDamage = 100;
	int GrenadeRange = 20;
	//medkit
	void UpgradeMedkitTicks(Player& p,Medkit& m);
	void UpgradeMedkitHeal(Player& p, Medkit& m);

	// Reset functions for when the player hits game over
	void resetWeaponUpgrades(Weapon& weap);
	void resetAllUpgrades();
	bool purchaseSuccess = false;
	vector<Harvestors> Harvestor;

	int GetWeaponPrice(int Price);							//Get the Price from Weapon class
	void BulletRefill(int BulletsInMagzine, int TotalBullets);//Get the 2 Values from Weapon class
	
	bool errorWindow = false;
	bool enablePurchaseWindow = false; //ensures only purchase result window is rendered.

private:
	short BulletPrice;
	Vector3 Position;
	int upgradeCost;
	
};


#endif // !ASTRONAUT_H
