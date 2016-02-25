#ifndef ENEMY_H
#define ENEMY_H
#include"Vector3.h"
#include <vector>
#include"GameObject.h"
#include "Camera3.h"
#include "Player.h"
#include "Bullet.h"

using std::vector;

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
	void EnemyMove(double dt,Player *p);				//move to find
	void EnemyTakeDmg(int Dmg);
	void EnemyShootAt(const double &dt,const float &bulletSpeed,Player *p);			//shooting of the enemy
	void BossShootAt(const double &dt, const float &bulletSpeed, Player *p);			//shooting of the enemy
	float findDirection();
	void update(Camera3 camera,const double &dt,Player *p);
	bool checkBulletCollision(Player *p);

	bool InRangeOfPlayer();		// dist away from player
	bool isDead();					//dead or not
	Vector3 target;
	Bullet projectile;
	float armRotate;
	float EnemySize;
	short spawnerCounter;
private:
	
	int range;
	int Hp;
	int AttackDamage;
	int MoveSpeed;
	short Resources;
	bool dead;
	double KiteTimer;
	bool moveRight;
	bool Shooting;
	float fireDelay;
	vector<Vector3> renderedBulletsDirection;
	vector<Vector3> renderedBulletsPosition;

	bool isBoss;
};




#endif // !ENEMY_H
