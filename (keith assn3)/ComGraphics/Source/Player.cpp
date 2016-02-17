#include"Player.h"

Player::Player(const int &hp) : HP(hp)
{
	Resources = 0;
}

Player::~Player()
{

}

int Player::GetHp()
{
	return HP;
}

int Player::ObtainResources(int amount)
{
	Resources += amount;
	return Resources;
}

float Player::getMiningAction()
{
	return MiningAction;
}

void Player::WhileMining(const double &dt)
{
	float speed = 500;
	if (isMining == true)
	{
		MiningAction += speed * dt;
		if (MiningAction >= 45.f)
		{
			MiningAction = 45.f;
			isMining = false;
		}
	}
	else
	{
		MiningAction -= speed * dt;
		if (MiningAction <= 0.f)
		{
			MiningAction = 0.f;
		}
	}
}
void Player::TakeDmg(int dmg)
{
	HP -= dmg;
}

void Player::RecoverHp(int recovered)
{
	HP += recovered;
}

void Player::changeWeapon(char weapon)
{
	WeaponState = weapon;
}

char Player::getWeaponState()
{
	return WeaponState;
}
int Player::getResources()
{
	return Resources;
}