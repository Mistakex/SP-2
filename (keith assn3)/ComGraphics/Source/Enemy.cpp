#include "Enemy.h"



Enemy::Enemy(int hp, int attack, int movespeed, Vector3 pos,int range)
{
	this->range = range;
}

Enemy::~Enemy()
{
}

void Enemy::EnemyMove(double dt)
{
	Vector3 view = target - EnemyPos;
	if (sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2)) >= range )
	{
		EnemyPos = EnemyPos - view*dt;
	}
}