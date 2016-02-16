#ifndef ROCK_H
#define ROCK_H
#include "Vector3.h"
class Rock
{
public:
	Rock(Vector3 pos,float SizeOfRock);
	~Rock();
	void ReduceSize();
	short GetResources();
	float GetSize();
private:
	float Size;

	Vector3 Position;
};




#endif // !ROCK_H