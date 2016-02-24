#ifndef SHIP_H
#define SHIP_H

#include "Camera3.h"
#include "GameObject.h"

class Ship :public GameObject
{
public:
	Ship(const Vector3 &pos,const Vector3 &range);
	~Ship();
	void init(Camera3 *camera);
	void cutscene(const double &dt);
private:
	Camera3 *Camera;
};


#endif