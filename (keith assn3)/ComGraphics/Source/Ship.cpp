#include "Ship.h"

Ship::Ship(const Vector3 &pos,const Vector3 &range)
{
	position = pos;
	rangexyz = range;
	cutsceneTimer = 0.f;
}

Ship::~Ship()
{

}

void Ship::init(Camera3 *camera)
{
	Camera = camera;
}

void Ship::cutscene(const double &dt)
{
	Camera->OnControls = false;
	Camera->target = position;
	cutsceneTimer += dt;
	if (cutsceneTimer < 2.f)
	{
		Camera->position = Vector3(0, 0, -35);
		position += Vector3(0, 3, 0)*dt;
	}
	else if (cutsceneTimer < 4.f)
	{
		Camera->position = (position.x, 0, position.z);
		position += Vector3(0, 3, 0)*dt;
	}
	else if (cutsceneTimer < 8.f)
	{
		Camera->position = position - Vector3(10, 3, 0);
		position += Vector3(100, 0, 0)*dt;
	}
}