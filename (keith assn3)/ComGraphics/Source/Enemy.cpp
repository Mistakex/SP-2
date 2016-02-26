#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector3 pos,Vector3 tar, Vector3 range, int hp, int attack, int movespeed,int range2,float size,bool Boss) : Hp(hp), AttackDamage(attack), MoveSpeed(movespeed)
{
	position = pos;
	target = tar;
	rangexyz = range;
	this->range = range2;
	KiteTimer = 0;
	Shooting = false;
	projectile.setView(Vector3(0, 0, 0));
	fireDelay = 0;
	armRotate = 0;
	EnemySize = size;
	isBoss = Boss;
	spawnerCounter = 0;
	bossIsSpawned = false;
	redAlien = false;
	redTimer = 0;
}

Enemy::~Enemy()
{
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

void Enemy::EnemyMove(double dt,Player *p)
{
	fireDelay += dt;

	Vector3 view = Vector3(0, 0, 0);
	if (target != position)
		view = (target - position).Normalized();
		
	if (!isBoss)
	{
		if (GetDistance() > range + KiteTimer)
		{
			position += Vector3(view.x,0,view.z)*MoveSpeed*dt;
			if (Shooting == true)
			{
				if (armRotate > 0)
					armRotate -= 90 * dt;
				projectile.moveBullet(dt, 70.f);
				checkBulletCollision(p);
			}
		}
		else if (KiteTimer < 7)
		{
			EnemyKite(dt);
			EnemyShootAt(dt,2.f,4.f, 10.f,p);
		}
		else if (KiteTimer >= 7)
		{
			EnemyShootAt(dt,2.f,4.f, 10.f,p);
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
			EnemyShootAt(dt, 2.f, 4.f, 10.f, p);
		}
	}
	else
	{
		BossShootAt(dt,1.f,3.f, 5.f, p);
	}
}

void Enemy::EnemyTakeDmg(int Dmg)
{
	if (Hp - Dmg >= 0)
		Hp -= Dmg;
	else
		Hp = 0;
}

void Enemy::EnemyShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p)
{
	if (fireDelay < startShooting)
	{
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			projectile.moveBullet(dt, 60.f);
			checkBulletCollision(p);
		}
		else
		{
			Shooting = true;
			projectile.updatePosition(Vector3(position));
			Vector3 bulletTarget = target + Vector3((rand() % 2) - 0.5f, (rand() % 2) / 2.f - 0.5f, (rand() % 2) / 2.f) - 0.5f;
			projectile.setView((bulletTarget - position).Normalized());
		}
	}
	else if (fireDelay >= endShooting)
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

void Enemy::BossShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p)
{
	if (fireDelay < startShooting)
	{
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			projectile.moveBullet(dt, 60.f);
			checkBulletCollision(p);
		}
		else
		{
			spawnerCounter++;
			Shooting = true;
			projectile.updatePosition(Vector3(position));
			Vector3 bulletTarget = target;
			projectile.setView((bulletTarget - position).Normalized());
		}
	}
	else if (fireDelay >= endShooting)
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

void Enemy::update(Camera3 camera,const double &dt, Player *p)
{
	if (redAlien)
	{
		redTimer += dt;
		if (redTimer > 0.3f)
		{
			redAlien = false;
			redTimer = 0.f;
		}
	}
	target = camera.position;
	EnemyMove(dt,p);
}

bool Enemy::checkBulletCollision(Player *p)
{
	float x = 0.5f, y = 1.f, z = 0.5f;
	if ((projectile.getPosition().x > target.x - x && projectile.getPosition().x < target.x + x
		&& projectile.getPosition().y > target.y - y && projectile.getPosition().x < target.y + y
		&& projectile.getPosition().z > target.z - z && projectile.getPosition().z < target.z + z)
		|| (projectile.getPosition() - target).Length() < 0.70f)
	{
		(*p).TakeDmg(AttackDamage);
		std::cout << (*p).GetHp() << std::endl;
		return true;
	}
	return false;
}