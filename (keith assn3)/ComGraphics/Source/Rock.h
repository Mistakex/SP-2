#ifndef ROCK_H
#define ROCK_H
#include "Vector3.h"
class Rock
{
public:
	Rock(Vector3 pos,float SizeOfRock);
	~Rock();
	void ReduceSize();
	int GetResources();
	float GetSize();

	int Resources;
	float Size;
	Vector3 Position;
private:
};




#endif // !ROCK_H