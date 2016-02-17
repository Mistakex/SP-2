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

float Player::WhileMining()
{
	return 0;
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