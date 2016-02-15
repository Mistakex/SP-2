#ifndef FLAG_H
#define FLAG_H
#include"Vector3.h"

class Flag
{
public:
	Flag();
	~Flag();
	float FlagHeightCoord();			//Flag rises return new coord
	float FlagTakeDmg();				//Flag minus hp
	float FlagRepair();					//Flag plus hp
private:
	float flagHp;	  //Hp of the flag base
	float flagRotate; // rotation of flag
	float flagheight; //Height of flag risen
	bool flagRise;    //if flag is risen
	bool ifEnemyflag; //Enemy or your flag
	Vector3 FLAG; // coordinates of flag
};




#endif // !FLAG_H
