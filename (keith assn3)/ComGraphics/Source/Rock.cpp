#include "Rock.h"


Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	position = pos;
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