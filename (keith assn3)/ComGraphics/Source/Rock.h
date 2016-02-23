#ifndef ROCK_H
#define ROCK_H
#include "Vector3.h"
#include "GameObject.h"
class Rock : public GameObject
{
public:
	Rock(Vector3 pos,float SizeOfRock);
	~Rock();
	void ReduceSize();
	int GetResources();
	float GetSize();

	int Resources;
	float Size;
private:
};




#endif // !ROCK_H