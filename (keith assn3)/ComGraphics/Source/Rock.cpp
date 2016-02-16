#include "Rock.h"


Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	Position = pos;
}

short Rock::GetResources()
{
	return (rand() % 5);
}
void Rock::ReduceSize()
{
	Size-=(rand()%2)/2;
	GetResources();
}
float Rock::GetSize()
{
	return Size;
}



Rock::~Rock()
{
}