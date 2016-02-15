#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int hp);
	~Player();
	int GetHp();
	int GetRecources();

	float WhileMining();	//increase and decrease the value for MiningAction
	void TakeDmg(int dmg);
	void RecoverHp(int recovered);

	int BulletsInClip;
	int TotalBullets;
	bool sprint;			//running or not
private:
	int HP;
	int Resources;
	float MiningAction;		//waving your pickaxe in da air
	char WeaponState;		//which weapon u using
};

Player::Player(int hp)
{
}

Player::~Player()
{
}


#endif // !PLAYER_H
