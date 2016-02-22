#ifndef ENEMY_H
#define ENEMY_H
#include"Vector3.h"
#include <vector>
#include"GameObject.h"
#include "Camera3.h"

using std::vector;

class Enemy: public GameObject
{
public:
	Enemy();
	Enemy(Vector3 pos, Vector3 tar, Vector3 range, int hp = 100, int attack = 5, int movespeed = 10, int range2 = 10, float size = 1);
	~Enemy();
	int GetEnemyHp();
	int GetEnemyAtt();
	int GetMovespeed();
	short GetResources();
	float GetDistance();
	bool GetShooting();
	
	Vector3 EnemyKiting();			//Shoot ,stop ,move again

	void EnemyKite(double dt);
	void EnemyMove(double dt);				//move to find
	void EnemyTakeDmg(int Dmg);
	void EnemyShootAt(const double &dt,const float &bulletSpeed);			//shooting of the enemy
	float findDirection();
	void update(Camera3 camera,const double &dt);

	bool InRangeOfPlayer();		// dist away from player
	bool isDead();					//dead or not
	Vector3 target;
	Vector3 bulletPos;
	Vector3 bulletTarget;
	float armRotate;
	float EnemySize;

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
	Vector3 bulletView;
	vector<Vector3> renderedBulletsDirection;
	vector<Vector3> renderedBulletsPosition;

};




#endif // !ENEMY_H
