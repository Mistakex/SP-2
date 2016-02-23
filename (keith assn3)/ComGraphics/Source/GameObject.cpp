#include "GameObject.h"

size_t GameObject::count = 0;

GameObject::GameObject()
{
	count++;
}

GameObject::~GameObject()
{
	count--;
}
