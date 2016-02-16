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
	float FlagHeightCoord(const float &target,const double &dt);			//Flag rises return new coord
	short FlagTakeDmg(const short &amount);				//Flag minus hp
	short FlagRepair();					//Flag plus hp
private:
	short flagHp;	  //Hp of the flag base
	float flagRotate; // rotation of flag
	float flagheight; //Height of flag risen
	bool flagRise;    //if flag is risen
	bool isEnemyflag; //Enemy or your flag
	Vector3 FLAG; // coordinates of flag
};

#endif // !FLAG_H
