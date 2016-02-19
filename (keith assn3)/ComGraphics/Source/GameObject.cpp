#include "GameObject.h"

vector<GameObject*> GameObject::allGameObjects;
size_t GameObject::count = 0;

GameObject::GameObject()
{
	count++;
	allGameObjects.push_back(this);
}

GameObject::~GameObject()
{
	//count--;
	//for (vector<GameObject*>::iterator it = allGameObjects.begin(); it != allGameObjects.end(); )
	//{
	//	if (*it == this)
	//	{
	//		it = allGameObjects.erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}
