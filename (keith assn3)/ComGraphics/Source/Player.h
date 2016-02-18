#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"

class Player
{
public:
	Player(const int &hp);
	~Player();
	int GetHp();
	int ObtainResources(int amount); // increase resources 

	void WhileMining(const double &dt);	//increase and decrease the value for MiningAction
	float getMiningAction();
	void TakeDmg(int dmg);
	void RecoverHp(int recovered);
	void changeWeapon(char weapon);
	char getWeaponState();
	int getResources();
	float getAngle(const Vector3 &view, const Vector3 &target);


	int BulletsInMagzine;
	int TotalBullets;		//Reloading
	bool sprint;			//running or not
	bool isMining;
	char WeaponState;		//which weapon u using
	
private:
	int HP;
	int Resources;
	float MiningAction;		//waving your pickaxe in da air
	
};
#endif // !PLAYER_H
