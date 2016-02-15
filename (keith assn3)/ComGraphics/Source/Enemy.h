#ifndef ENEMY_H
#define ENEMY_H
#include"Vector3.h"
class Enemy
{
public:
	Enemy(int hp,int attack,int movespeed,Vector3 pos,int range);
	~Enemy();
	int GetEnemyHp();
	int GetEnemyAtt();
	int GetMovespeed();
	short GetResources();
	float GetDistance();
	

	Vector3 GetEnemypos();
	Vector3 EnemyKiting();			//Shoot ,stop ,move again

	void EnemyMove(double dt);				//move to find
	void EnemyTakeDmg(int Dmg);
	void EnemyShootAt();			//accuracy of the enemy

	bool InRangeOfPlayer();		// dist away from player
	bool isDead();					//dead or not
private:
	int Hp;
	int AttackDamage;
	int MoveSpeed;
	int range;
	short Resources;
	bool dead;
	bool InrangeTokite;					//in range to start kiteing

	Vector3 EnemyPos;
	Vector3 target;
};




#endif // !ENEMY_H
