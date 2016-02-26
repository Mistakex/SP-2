#include "Harvestors.h"

Harvestors::Harvestors(Vector3 pos, const float &movespd) :MoveSpeed(movespd)
{
	Position = pos;
}
void Harvestors::MoveTowards(Vector3 pos, double dt)
{
	Target = pos;
	view = Target - Position;
	if (pow(Target.x - Position.x, 2) + pow(Target.z - Position.z, 2) > 2)
	{	
		view.Normalized();
		Position += view*MoveSpeed*(float)dt;
	}
}
void Harvestors::MineRocks(Rock& rock,Player& a)
{
	rock.ReduceSize();
	a.ObtainResources(rock.GetResources());
}
void Harvestors::FindDirection()
{
	view = Target - Position;
	if (Target.z > Position.z)
		Rotation = Math::RadianToDegree(atan(view.x / view.z)) - 180;
	else
		Rotation = Math::RadianToDegree(atan(view.x / view.z));
}
float Harvestors::GetHarvestorRotation()
{
	return Rotation;
}
Harvestors::~Harvestors()
{
}
