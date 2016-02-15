#ifndef ASSIGNMENT_1_H
#define ASSIGNMENT_1_H

#include "Scene.h"
#include "MyMath.h"

#define PI 3.1415926535897932384626433832795

class Assignment1 : public Scene
{

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	enum COLOUR_TYPE
	{
		WHITE = 0,
		GREEN,
		BLUE,
		BLACK,
		BROWN,
		RED,
		PINK,
		YELLOW,
		WHITE_2,
		ORANGE,
		NUM_COLOUR
	};

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_RECTANGLE_2,
		GEO_CIRCLE_3,
		GEO_RTRIANGLE_4,
		NUM_GEOMETRY
	};
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_COLOUR];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	// bird stuff
	float birdrotation;
	bool birdrotatecheck;
	bool birdMovingcheck;
	float birdMovingX;
	// end of bird stuff

	// cloud moving //
	float cloudTranslateX;
	// end of cloud movement //

	//tree stuff//
	float leavesSwayX;
	bool leavesStop;
	// end of treestuff//

	// boat moving //
	float boatScaling;
	float boatTranslateX;
	bool boatStop;
	float wavesSwayX, wavesSwayY;
	bool waveStop;
	// end of boat moving//

	// hiding rabbit //
	float hideDelay, hideRotate;
	bool checkRabbitRotate,checkHideDelay;
	// rabbit hiding end //

	// butterfly moving //
	float butterflyWingSwing;
	bool butterflyStop;
	// butterfly end //
public:
	Assignment1();
	~Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


};

#endif