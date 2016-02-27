#ifndef GRENADE_H
#define GRENADE_H

#include "Vector3.h"
#include "CountDown.h"
#include "Enemy.h"
class Grenade
{
public:
	Grenade(Vector3 pos , Vector3 target,const int& damage ,const int& Range);
	~Grenade();
	void ThrowGrenade(double dt);
	void DealDamage(Enemy& enemy);
	void GetExplosion();
	Vector3 GetPosition();
	Countdown throwGrenade;
	Grenade& operator=(const Grenade& nade);
	void LookAt();
	float LookAtDirection;
	float GrenadeRotation;
	float size;
	bool Explode;
private:
	const int Range;
	const int damage;
	Vector3 Position;
	Vector3 Target;
	Vector3 View;
};



#endif // !GRENADE_H
