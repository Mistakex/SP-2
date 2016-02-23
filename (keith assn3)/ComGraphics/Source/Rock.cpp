#include "Rock.h"


Rock::Rock(Vector3 pos, float SizeOfRock)
{
	Size = SizeOfRock;
	position = pos;
	rangexyz = Vector3(SizeOfRock, SizeOfRock, SizeOfRock)*0.8f;
}

int Rock::GetResources()
{
	Resources = (rand() % 5+1);
	return Resources;
}
void Rock::ReduceSize()
{
	Size -= 0.5;
	rangexyz -= Vector3(0.5f, 0.5f, 0.5f);
}
float Rock::GetSize()
{
	return Size;
}



Rock::~Rock()
{
}