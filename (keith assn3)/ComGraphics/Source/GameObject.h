#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector3.h"
#include <vector>

using std::vector;

class GameObject
{
public:
	virtual ~GameObject();
	Vector3 position;
	Vector3 range;
	static vector<GameObject*> allGameObjects;
	static size_t count;
protected:
	GameObject();
};

#endif