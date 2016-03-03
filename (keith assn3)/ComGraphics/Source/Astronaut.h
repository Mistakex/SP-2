/******************************************************************************/
/*!
\file	Astronaut.h
\author Lim Zhi Yuan
\par	email: 153432K@mymail.nyp.edu.sg
\brief
Class for the Astronaut, which functions as the shop for players to upgrade, and
purchase items.
*/
/******************************************************************************/

#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Vector3.h"
#include "Weapon.h"
#include "Player.h"
#include "Harvestors.h"
#include "Medkit.h"
#include <string.h>

using std::string;

/******************************************************************************/
/*!
Class Astronaut:
\brief	Astronaut functions - Purchase and Upgrading of other items.
*/
/******************************************************************************/
class Astronaut
{
public:
	Astronaut(Vector3 pos);
	~Astronaut();
	Vector3 GetAstronautPos();
	vector<Harvestors> Harvestor;

	// Upgrade Functions and variables
	void UpgradeWeapon(Weapon& weap, Player& p);							//int Damage is from Weapon class		
	void UpgradeTurret(Player& p);
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
	void resetMedkitUpgrades(Medkit& m);
	void resetAllUpgrades();

	// Bools for result of purchase, to ensure that only one result window is rendered.
	bool upgradeSuccess = false;
	bool purchaseSuccess = false;
	bool errorWindow = false;
	bool enablePurchaseWindow = false; 

private:
	Vector3 Position;
};

#endif // !ASTRONAUT_H
