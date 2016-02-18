#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "Vector3.h"
class Turret
{
public:
	Turret(const int&hp, const int&dmg, const Vector3 &pos);
	~Turret();
	bool TargetDead(Enemy enemy);
	void nextTarget(Enemy enemy);
	void ReduceHp();

private:
	int Hp;
	const int damage;
	const Vector3 position;
	Vector3 Target;
};



#endif // !TURRET_H
