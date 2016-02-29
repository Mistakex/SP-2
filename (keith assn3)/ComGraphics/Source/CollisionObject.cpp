#include "CollisionObject.h"

CollisionObject::CollisionObject(Vector3 position, float circle, Vector3 rangexyz)
{
	this->position = position;
	this->rangexyz = rangexyz;
	circleRange = circle;
}

CollisionObject::~CollisionObject()
{

}