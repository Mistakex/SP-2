#include "Enemy.h"

vector<Enemy*> Enemy::Aliens2;

Enemy::Enemy(Vector3 pos,Vector3 tar, int hp, int attack, int movespeed, int range) : Hp(hp), AttackDamage(attack), MoveSpeed(movespeed)
{
	position = pos;
	target = tar;
	this->range = range;
	KiteTimer = 0;
	Shooting = false;
	bulletPos = Vector3(0, 0, 0);
	bulletTarget = Vector3(0, 0, 0);
	fireDelay = 0;
	armRotate = 0;

	Aliens2.push_back(this);
}

Enemy::~Enemy()
{
	for (vector<Enemy*>::iterator it = Aliens2.begin(); it != Aliens2.end();)
	{
		if (*it == this)
		{
			it = Aliens2.erase(it);
		}
		else
		{
			it++;
		}
	}
}

int Enemy::GetEnemyHp()
{
	return Hp;
}

int Enemy::GetEnemyAtt()
{
	return AttackDamage;
}

int Enemy::GetMovespeed()
{
	return MoveSpeed;
}

short Enemy::GetResources()
{
	return Resources;
}

float Enemy::GetDistance()
{
	Vector3 view = target - position;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

bool Enemy::GetShooting()
{
	return Shooting;
}

void Enemy::EnemyMove(double dt)
{
	fireDelay += dt;
	Vector3 view = Vector3(0, 0, 0);
	if (target != position)
		view = (target - position).Normalized();
		
	if (GetDistance() > range + KiteTimer)
	{
		position += Vector3(view.x,0,view.z)*MoveSpeed*dt;
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			bulletPos += bulletView*10*dt;
		}
	}
	else if (KiteTimer < 7)
	{
		EnemyKite(dt);
		EnemyShootAt(dt, 10);
	}
	else if (KiteTimer >= 7)
	{
		EnemyShootAt(dt, 10);
		KiteTimer = 0;
		if (rand() % 2 == 0)
		{
			moveRight = true;
		}
		else
		{
			moveRight = false;
		}
	}
	else
	{
		EnemyShootAt(dt, 10);
	}
}

void Enemy::EnemyTakeDmg(int Dmg)
{
	Hp -= Dmg;
}

void Enemy::EnemyShootAt(const double &dt,const float &bulletSpeed)
{
	if (fireDelay < 3)
	{
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			bulletPos += bulletView*bulletSpeed*dt;
		}
		else
		{
			Shooting = true;
			bulletPos = position;
			bulletTarget = target + Vector3((rand() % 2)/2.f, (rand() % 2)/2.f, (rand() % 2)/2.f);
			bulletView = bulletTarget - position;
		}
	}
	else if (fireDelay >= 5)
	{
		fireDelay = 0;
	}
	else
	{
		if (armRotate < 90)
		{
			armRotate += 90 * dt;
		}
		Shooting = false;
	}
}


float Enemy::findDirection()
{
	Vector3 view = target - position;
	if (target.z > position.z)
		return Math::RadianToDegree(atan(view.x / view.z)) - 180;
	else
		return Math::RadianToDegree(atan(view.x / view.z));
}

void Enemy::EnemyKite(double dt)
{
	KiteTimer += dt;
	if (KiteTimer < 3)
	{
		Vector3 view = Vector3(0, 0, 0);
		if (target != position)
			view = (target - position).Normalized();
		Vector3 right = view.Cross(Vector3(0, 1, 0));
		if (moveRight == true)
			position += right*(MoveSpeed / 4)*dt;
		else
			position -= right*(MoveSpeed / 4)*dt;
	}
}

bool Enemy::InRangeOfPlayer()
{
	if (GetDistance() >= range)
	{
		return false;
	}
	else
		return true;
}

bool Enemy::isDead()
{
	if (Hp <= 0)
	{
		return true;
	}
	else
		return false;
}