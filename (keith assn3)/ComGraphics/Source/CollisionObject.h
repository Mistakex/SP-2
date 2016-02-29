#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

#include "GameObject.h"
#include "Vector3.h"

class CollisionObject : public GameObject
{
public:
	CollisionObject(Vector3 position, float circle, Vector3 rangexyz = Vector3(1,1,1));
	~CollisionObject();
	float circleRange;
};


#endif