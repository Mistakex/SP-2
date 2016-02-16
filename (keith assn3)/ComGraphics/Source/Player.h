#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(const int &hp);
	~Player();
	int GetHp();
	int GetResources(int amount);

	float WhileMining();	//increase and decrease the value for MiningAction
	void TakeDmg(int dmg);
	void RecoverHp(int recovered);
	void changeWeapon(char weapon);
	char getWeaponState();

	int TotalBullets; //Reloading
	bool sprint;			//running or not
	char WeaponState;		//which weapon u using
private:
	int HP;
	int Resources;
	float MiningAction;		//waving your pickaxe in da air
	
};
#endif // !PLAYER_H
