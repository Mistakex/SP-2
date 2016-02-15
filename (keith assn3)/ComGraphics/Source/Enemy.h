#ifndef ENEMY_H
#define ENEMY_H
#include"Vector3.h"
class Enemy
{
public:
	Enemy(Vector3 pos,Vector3 tar,int hp = 100, int attack = 5, int movespeed = 10, int range = 10);
	~Enemy();
	int GetEnemyHp();
	int GetEnemyAtt();
	int GetMovespeed();
	short GetResources();
	float GetDistance();
	

	Vector3 GetEnemypos();
	Vector3 EnemyKiting();			//Shoot ,stop ,move again

	void EnemyKite(double dt);
	void EnemyMove(double dt);				//move to find
	void EnemyTakeDmg(int Dmg);
	void EnemyShootAt(Vector3 target);			//accuracy of the enemy
	float findDirection();

	bool InRangeOfPlayer();		// dist away from player
	bool isDead();					//dead or not
	Vector3 EnemyPos;
	Vector3 target;
private:
	int Hp;
	int AttackDamage;
	int MoveSpeed;
	int range;
	short Resources;
	bool dead;
	double KiteTimer;
	bool moveRight;


};




#endif // !ENEMY_H
