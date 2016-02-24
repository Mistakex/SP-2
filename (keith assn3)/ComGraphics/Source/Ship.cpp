#include "Ship.h"

Ship::Ship(const Vector3 &pos,const Vector3 &range)
{
	position = pos;
	rangexyz = range;
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
	Camera->position = position + Vector3(0, 10, 0);
}