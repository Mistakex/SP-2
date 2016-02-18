#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Vector3.h"
class Turret
{
public:
	Turret(const int&hp, const int&dmg, const Vector3 &pos);
	~Turret();

	void nextTarget(Enemy enemy,Enemy nextEnemy);//*************Might Get Subscript error if not careful.
	void ReduceHp(int dmg);

private:
	int Hp;
	const int damage;
	const Vector3 position;
	Vector3 Target;
};



#endif // !TURRET_H
