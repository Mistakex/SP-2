/******************************************************************************/
/*!
\file	Enemy.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Enemies shooting and finding their way to the player, including the boss
*/
/******************************************************************************/

#ifndef ENEMY_H
#define ENEMY_H
#include"Vector3.h"
#include <vector>
#include"GameObject.h"
#include "Camera3.h"
#include "Player.h"
#include "Bullet.h"
#include "Turret.h"

using std::vector;

/******************************************************************************/
/*!
Class Enemy:
\brief	Enemy stats and functions. It is a child of GameObject
*/
/******************************************************************************/

class Enemy: public GameObject
{
public:
	Enemy();
	Enemy(Vector3 pos, Vector3 tar, Vector3 range, int hp = 100, int attack = 5, int movespeed = 10, int range2 = 10, float size = 1,bool Boss = false);
	~Enemy();
	int GetEnemyHp();
	int GetEnemyAtt();
	int GetMovespeed();
	short GetResources();
	float GetDistance();
	bool GetShooting();
	
	Vector3 EnemyKiting();			//Shoot ,stop ,move again

	void EnemyKite(double dt);
	void EnemyMove(double dt, Player *p, vector<Turret> *Turrets);				//move to find
	void EnemyTakeDmg(int Dmg);
	void EnemySetHp(const int &Hp);
	void EnemyShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p, vector<Turret> *Turrets);			//shooting of the enemy
	void BossShootAt(const double &dt, const float &startShooting, const float &endShooting);			//shooting of the enemy
	void BossSpawnMinions(const double &dt);
	float findDirection();
	void update(Camera3 camera,const double &dt,Player *p,vector<Turret> *Turrets);
	bool checkBulletCollision(Player *p, vector<Turret> *Turrets);
	bool checkBulletsCollision(Player *p, vector<Turret> *Turrets);

	bool InRangeOfPlayer();		// dist away from player
	bool isDead();					//dead or not
	Vector3 target;
	Bullet projectile;
	Bullet projectiles[10];
	int currentBullet;
	float armRotate;
	float EnemySize;
	short spawnerCounter;
	bool bossIsSpawned;
	bool redAlien;
	bool startSpawningMinions;
	float spawnDelay;
private:
	int range;
	int Hp;
	int AttackDamage;
	int MoveSpeed;
	short Resources;
	double KiteTimer;
	bool moveRight;
	bool Shooting;
	float fireDelay;
	float redTimer;
	vector<Vector3> renderedBulletsDirection;
	vector<Vector3> renderedBulletsPosition;

	int turretNumber;
	bool isBoss;
};

#endif // !ENEMY_H
