#include "Rock.h"


Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
}

short Rock::GetResources()
{
	return (rand() % 5);
}
void Rock::ReduceSize()
{
	Size -= 0.5;
	GetResources();
}
float Rock::GetSize()
{
	return Size;
}



Rock::~Rock()
{
}