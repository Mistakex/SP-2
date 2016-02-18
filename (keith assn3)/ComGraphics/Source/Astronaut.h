#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Vector3.h"
#include "Weapon.h"
#include "Player.h"
class Astronaut
{
public:
	Astronaut(Vector3 pos);
	~Astronaut();
	Vector3 GetAstronautPos();
	void AstronautMoveAround();						//The astronaut move around the spaceship in a random amount of steps
	Weapon UpgradeWeapon(Weapon weap, Player p);							//int Damage is from Weapon class		
	int GetWeaponPrice(int Price);							//Get the Price from Weapon class
	void BulletRefill(int BulletsInMagzine, int TotalBullets);//Get the 2 Values from Weapon class
	bool playerIsNear = false;

private:
	short BulletPrice;
	Vector3 Position;
	int upgradeCost;
};


#endif // !ASTRONAUT_H
