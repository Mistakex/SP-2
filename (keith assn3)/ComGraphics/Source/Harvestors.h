#ifndef HARVESTORS_H
#define HARVESTORS_H
#include "Vector3.h"
#include "Rock.h"
#include "Player.h"
class Harvestors
{
public:
	Harvestors(Vector3 pos,const float &movespeed);
	~Harvestors();
	void MoveTowards(Vector3 pos,double dt);
	void FindDirection();
	void MineRocks(Rock &rock,Player& a);
	float GetHarvestorRotation();
	Vector3 Position;
private:
	Vector3 view;
	Vector3 Target;
	float Rotation;
	const float MoveSpeed;
};


#endif // !HARVESTORS_H
