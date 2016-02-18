#ifndef FLAG_H
#define FLAG_H
#include"Vector3.h"

class Flag
{
public:
	//Constructors : Defaulting HP as 100, friendly flag.
	Flag();
	Flag(const Vector3 &coords);
	~Flag();
	float FlagHeightIncrease(const float &target, const double &dt);			//Flag rises return new coord
	float FlagHeightDecrease(const float &target, const double &dt);
	float getMagnitude(const Vector3 &target);

	Vector3 FLAGPOLE; // coordinates of flag
	Vector3 FLAG;
	float flagheight; //Height of flag
	bool flagIsBlue = false;
private:

	float flagRotate; // rotation of flag

	bool flagRise;    //if flag is risen
	bool isEnemyflag; //Enemy or your flag

};

#endif // !FLAG_H
