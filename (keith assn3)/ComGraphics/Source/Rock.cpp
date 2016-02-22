#include "Rock.h"


Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
}

int Rock::GetResources()
{
	Resources = (rand() % 5+1);
	return Resources;
}
void Rock::ReduceSize()
{
	Size -= 0.5;
}
float Rock::GetSize()
{
	return Size;
}



Rock::~Rock()
{
}