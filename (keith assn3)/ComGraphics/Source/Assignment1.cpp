#include "Assignment1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "shader.hpp"



Assignment1::Assignment1()
{
}

Assignment1::~Assignment1()
{
}

void Assignment1::Init()
{
	glEnable(GL_DEPTH_TEST);
	// Set background color to dark blue
	glClearColor(0.0f, 0.9f, 0.8f, 0.0f);
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
		// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_COLOUR, &m_colorBuffer[0]);
	
	//------------------------------------------ vertex buffers -----------------------------------//
	static const GLfloat vertex_buffer_data[] = /// equilateral triangle
	{
		-1.0f, -1.0f, 0.0f, //vertex 0 of triangle
		1.0f, -1.0f, 0.0f, //vertex 1 of triangle
		0.0f, 1.0f, 0.0f, //vertex 2 of triangle
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data2[] = /// rectangle
	{
		-1.0f, 1.0f, 0.0f, //vertex 0 of triangle
		-1.0f, 0.0f, 0.0f, //vertex 1 of triangle
		0.0f, 1.0f, 0.0f, //vertex 2 of triangle
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

	static GLfloat vertex_buffer_data3[108]; /// parts for circle
	
	for (int i = 0; i < 36; ++i)
	{
		if (i % 3 != 2)
		{
			vertex_buffer_data3[i * 3] = sin(i*11 * (PI/180));
			vertex_buffer_data3[i * 3 + 1] = cos(i*11 * (PI / 180));
			vertex_buffer_data3[i * 3 + 2] = 0.0;
		}
		else
		{
			vertex_buffer_data3[i * 3] = 0.0;
			vertex_buffer_data3[i * 3 + 1] = 0.0;
			vertex_buffer_data3[i * 3 + 2] = 0.0;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data4[] = /// right angled triangle
	{
		-1.0f, 1.0f, 0.0f, //vertex 0 of triangle
		1.0f, -1.0f, 0.0f, //vertex 1 of triangle
		-1.0f, -1.0f, 0.0f //vertex 2 of triangle
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RTRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

	//---------------------------------------- color buffers--------------------------------------------//
	static GLfloat color_buffer_data[108]; /// WHITE
	for (int i = 0; i < 108; ++i)
	{
		color_buffer_data[i] = 1.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),color_buffer_data, GL_STATIC_DRAW);

	static GLfloat color_buffer_data2[108]; // GREEN
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data2[i*3] = 0.0;
		color_buffer_data2[i * 3 + 1] = 0.8;
		color_buffer_data2[i * 3 + 2] = 0.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GREEN]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	static GLfloat color_buffer_data3[108]; // BLUE
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data3[i * 3] = 0.0;
		color_buffer_data3[i * 3 + 1] = 0.5;
		color_buffer_data3[i * 3 + 2] = 1.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLUE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data4[] = { // BLACK
		0.0f, 0.0f, 0.0f, //color of vertex 0
		0.0f, 0.0f, 0.0f, //color of vertex 1
		0.0f, 0.0f, 0.0f, //color of vertex 2
		0.0f, 0.0f, 0.0f, //color of vertex 0
		0.0f, 0.0f, 0.0f, //color of vertex 1
		0.0f, 0.0f, 0.0f, //color of vertex 2
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);

	static GLfloat color_buffer_data5[108]; // BROWN
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data5[i * 3] = 0.5;
		color_buffer_data5[i * 3 + 1] = 0.3;
		color_buffer_data5[i * 3 + 2] = 0.2;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BROWN]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);

	static GLfloat color_buffer_data6[108]; // RED
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data6[i * 3] = 1.0;
		color_buffer_data6[i * 3 + 1] = 0.0;
		color_buffer_data6[i * 3 + 2] = 0.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RED]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data6), color_buffer_data6, GL_STATIC_DRAW);

	static GLfloat color_buffer_data7[108]; // PINK
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data7[i * 3] = 0.9;
		color_buffer_data7[i * 3 + 1] = 0.3;
		color_buffer_data7[i * 3 + 2] = 0.7;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PINK]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data7), color_buffer_data7, GL_STATIC_DRAW);

	static GLfloat color_buffer_data8[108]; // yellow
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data8[i * 3] = 0.9;
		color_buffer_data8[i * 3 + 1] = 0.9;
		color_buffer_data8[i * 3 + 2] = 0.3;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data8), color_buffer_data8, GL_STATIC_DRAW);

	static GLfloat color_buffer_data9[108]; // WHITE 2
	for (int i = 0; i < 108; ++i)
	{
		color_buffer_data9[i] = 0.9;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data9), color_buffer_data9, GL_STATIC_DRAW);

	static GLfloat color_buffer_data10[108]; // ORANGE
	for (int i = 0; i < 36; ++i)
	{
		color_buffer_data10[i * 3] = 1.0;
		color_buffer_data10[i * 3 + 1] = 0.5;
		color_buffer_data10[i * 3 + 2] = 0.0;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ORANGE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data10), color_buffer_data10, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Use our shader
	glUseProgram(m_programID);

	// bird
	birdrotation = 5;
	birdrotatecheck = true;
	birdMovingX = 0;
	birdMovingcheck = true;
	// end of bird

	// cloud
	cloudTranslateX = -40;
	// end of cloud

	//big tree leaves
	leavesSwayX = 0;
	leavesStop = true;
	// end of tree leaves

	// boat stuff
	boatScaling = 1;
	boatTranslateX = 0;
	boatStop = true;
	wavesSwayX = 0;
	wavesSwayY = 0;
	waveStop = true;
	// end of boat

	//butterfly stuff
	butterflyWingSwing = 0;
	butterflyStop = true;
	//butterfly stuff

	//hiding rabbit stuff
	hideDelay = 0, hideRotate = 0;
	checkRabbitRotate = true,checkHideDelay = false;
	// end of hiding rabbit stuff
}



void Assignment1::Update(double dt)
{
	/// -----------------------------------------bird movements------------------------------------ ///

	if (birdrotatecheck == true && birdrotation < 30)
	{
		birdrotation += (float)(50 * dt) ;
		if (birdrotation >= 30)
		{
			birdrotatecheck = false;
		}
	}
	else if (birdrotatecheck == false && birdrotation > 5)
	{
		birdrotation -= (float)(50 * dt);
		if (birdrotation <= 5)
		{
			birdrotatecheck = true;
		}
	}

	int birdDriftSpeed = 5;

	if (birdMovingcheck == true && birdMovingX < 10)
	{
		birdMovingX += (float)(birdDriftSpeed* dt);
		if (birdMovingX >= 10)
		{
			birdMovingcheck = false;
		}
	}
	else if (birdMovingcheck == false && birdMovingX > 0)
	{
		birdMovingX -= (float)(birdDriftSpeed * dt);
		if (birdMovingX <= 0)
		{
			birdMovingcheck = true;
		}
	}
	
	// -----------------------------------------start of cloud movement----------------------------------------- ///
	int CloudDriftSpeed = 6;

	if (cloudTranslateX <= 60)
	{
		cloudTranslateX += (float)(CloudDriftSpeed * dt);
	}
	else
	{
		cloudTranslateX = -50;
	}


	//-----------------------------------------tree leaves movement-----------------------------------------//
	int TreeSwaySpeed = 1;

	if (leavesStop == true && leavesSwayX <= 1)
	{
		leavesSwayX += (float)(TreeSwaySpeed* dt);
		if (leavesSwayX > 1)
		{
			leavesStop = false;
		}
	}
	else if (leavesStop == false && leavesSwayX >= 0)
	{
		leavesSwayX -= (float)(TreeSwaySpeed* dt);
		if (leavesSwayX < 0)
		{
			leavesStop = true;
		}
	}

	//----------------------------------------- Boat Movement -----------------------------------------//

	float BoatSpeed = 10;

	if (boatStop == true && boatTranslateX <= 20)
	{
		if (boatTranslateX <= 10)
		{
			boatTranslateX += (float)(BoatSpeed* dt);
			boatScaling += (float)(0.1*dt);
		}
		else
		{
			boatTranslateX += (float)(BoatSpeed/2* dt);
			boatScaling += (float)(0.1/2*dt);
		}
		if (boatTranslateX > 20)
		{
			boatStop = false;
		}
	}
	else if (boatStop == false && boatTranslateX >= -55)
	{
		if (boatTranslateX >= -45)
		{
			boatTranslateX -= (float)(BoatSpeed* dt);
			boatScaling -= (float)(0.1*dt);
		}
		else
		{
			boatTranslateX -= (float)(BoatSpeed / 2 * dt);
			boatScaling -= (float)(0.1/2*dt);
		}
		if (boatTranslateX < -55)
		{
			boatStop = true;
		}
	}
	
	//----------------------------------------- wave movement -----------------------------------------//
	int WaveSwaySpeed = 2;

	if (waveStop == true)
	{
		if (boatStop == true)
		{
			wavesSwayX += (float)(WaveSwaySpeed* dt);
		}
		else
		{
			wavesSwayX -= (float)(WaveSwaySpeed* dt);
		}

		wavesSwayY += (float)(WaveSwaySpeed* dt);

		if (wavesSwayY > 1)
		{
			waveStop = false;
		}
	}
	else if (waveStop == false)
	{
		if (boatStop == true)
		{
			wavesSwayX -= (float)(WaveSwaySpeed* dt);
		}
		else
		{
			wavesSwayX += (float)(WaveSwaySpeed* dt);
		}
		
		wavesSwayY -= (float)(WaveSwaySpeed* dt);

		if (wavesSwayY < 0)
		{
			waveStop = true;
		}
	}

	//----------------------------------------- butterfly movement-----------------------------------------//
	int butterflySpeed = 5;

	if (butterflyStop == true)
	{
		if (butterflyWingSwing <= 1)
		{
			butterflyWingSwing += (float)(butterflySpeed* dt);
		}
		else
		{
			butterflyStop = false;
		}
	}
	else if (butterflyStop == false)
	{
		if (butterflyWingSwing >= 0)
		{
			butterflyWingSwing -= (float)(butterflySpeed* dt);
		}
		else
		{
			butterflyStop = true;
		}
	}

	// -----------------------------------------hiding rabbit-----------------------------------------//
	float rabbitspeed = 30;
	if (checkRabbitRotate == true)
	{
		if (checkHideDelay == true)
		{
			hideRotate += (float)(rabbitspeed * dt);
			if (hideRotate > 70)
			{
				checkRabbitRotate = false;
				checkHideDelay = false;
			}
		}
		else
		{
			hideDelay += dt;
			if (hideDelay >= 1)
			{
				hideDelay = 0;
				checkHideDelay = true;
			}
		}
	}
	else if (checkRabbitRotate == false)
	{

		if (checkHideDelay == true)
		{
			hideRotate -= (float)(rabbitspeed* 5 * dt);
			if (hideRotate < 0)
			{
				checkRabbitRotate = true;
				checkHideDelay = false;
			}
		}
		else
		{
			hideDelay += dt;
			if (hideDelay >= 1)
			{
				hideDelay = 0;
				checkHideDelay = true;
			}
		}

	}
}

void Assignment1::Render()
{
	// Render VBO here
	// Clear color and depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10);

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1);

	float extraBirdMovingX = birdMovingX;
	// -------------------------------------------------birds flying-------------------------------------------------//
	for (int i = 0; i < 3; i++)
	{
		// left wing
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		float leftwingX = 8 - i * 6, leftwingY = 28 + i * (-3), wingsZ = 1;

		if (i == 1)
		{
			birdMovingX = -birdMovingX;
		}
		else
		{
			birdMovingX = extraBirdMovingX;
		}

		scale.SetToScale(2, 0.5, 0);
		rotate.SetToRotation(-birdrotation, 0, 0, 1);
		translate.SetToTranslation(leftwingX + birdMovingX, leftwingY, wingsZ);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(1, 0.3, 0);
		rotate.SetToRotation(-birdrotation, 0, 0, 1);
		translate.SetToTranslation(leftwingX - 1 + birdMovingX, leftwingY - 0.1 + birdrotation / 50, wingsZ + 0.1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

		// right wing

		float rightwingX = leftwingX + 3, rightwingY = leftwingY;
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(2, 0.5, 0);
		rotate.SetToRotation(birdrotation, 0, 0, 1);
		translate.SetToTranslation(rightwingX + birdMovingX, rightwingY, wingsZ);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(1, 0.3, 0);
		rotate.SetToRotation(birdrotation, 0, 0, 1);
		translate.SetToTranslation(rightwingX + 1 + birdMovingX, rightwingY - 0.1 + birdrotation / 50, wingsZ + 0.1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	}


	//------------------------------------------------- end of birds flying-------------------------------------------------//


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	// 2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GREEN]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	// ------------------------------------------------- grass -------------------------------------------------//

	scale.SetToScale(100, 30, 1);
	rotate.SetToRotation(-5, 0, 0, 1);
	translate.SetToTranslation(40, -50, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(100, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(40, -7, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	//-------------------------------------------------end of grass-------------------------------------------------//


	// -------------------------------------------------river-------------------------------------------------//
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	// 2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLUE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(100, 30, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(40, -37, -1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	// -------------------------------------------------end of river-------------------------------------------------//

	///------------------------------------------------- cloud------------------------------------------------- ///
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	for (int x = 0; x < 3; x++)
	{
		if (x == 1)
		{
			scale.SetToScale(4.5, 4.5, 0);
		}
		else
		{
			scale.SetToScale(3, 3, 0);
		}
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0 + x * 4 + cloudTranslateX, 22, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
	
	}

	for (int x = 0; x < 3; x++)
	{
		if (x == 1)
		{
			scale.SetToScale(1.5, 1.5, 0);
		}
		else
		{
			scale.SetToScale(1, 1, 0);
		}
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-20 + x * 1 + cloudTranslateX, 25, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	}
	// -------------------------------------------------cloud reflection-------------------------------------------------//
	for (int x = 0; x < 3; x++)
	{
		if (x == 1)
		{
			scale.SetToScale(-4.5, -4.5, 0);
		}
		else
		{
			scale.SetToScale(-3, -3, 0);
		}
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(0 + x * 4 + cloudTranslateX, -18, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		for (int x = 0; x < 3; x++)
		{
			if (x == 1)
			{
				scale.SetToScale(-1.5, -1.5, 0);
			}
			else
			{
				scale.SetToScale(-1, -1, 0);
			}
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(-20 + x * 1 + cloudTranslateX, -21, 0);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		}
	}

	/// -------------------------------------------------end of cloud -------------------------------------------------///

	//-------------------------------------------------start of sun -------------------------------------------------////
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);


	scale.SetToScale(10, 10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(30, 30, -1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(12, 12, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(30, 30, -1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
	
	//------------------------------------------------- sun reflection -------------------------------------------------//
	scale.SetToScale(-10, -10, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(30, -26, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(-12, -12, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(30, -26, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	//-------------------------------------------------end of sun------------------------------------------------- //

	/// -------------------------------------------------tree------------------------------------------------- ///
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	// 2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BROWN]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(7, 50, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-33, -20, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // tree trunk


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(3, 5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-33, -15, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

	for (int i = 0; i < 3; i++)
	{
		scale.SetToScale(3, 6, 0);
		if (i == 2)
		{
			rotate.SetToRotation(225, 0, 0, 1);
		}
		else
		{
			rotate.SetToRotation(180, 0, 0, 1);
		}
		translate.SetToTranslation(-39.5 + i*5, -22, 3);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	// ** -------------------------------------------------branches of tree------------------------------------------------- **//
	for (int i = 0; i < 2; i++)
	{
		scale.SetToScale(2, 20, 0);
		rotate.SetToRotation(-45 + i*10, 0, 0, 1);
		translate.SetToTranslation(-35 + i*10, 6+ i*10, 2);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
	}


	scale.SetToScale(2, 20, 0);
	rotate.SetToRotation(-45, 0, 0, 1);
	translate.SetToTranslation(-38, 17, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GREEN]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	for (int x = 3; x > 0; x--) // one whole bunch of leaves
	{
		for (int y = 0; y < 1+ x; y++)
		{
			scale.SetToScale(4 + leavesSwayX, 4 + leavesSwayX, 0);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(-35 + y * 4, 25 - x*3, 4);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
		
		}
	}

	for (int x = 2; x > 0; x--) // one whole bunch of leaves
	{
		for (int y = 0; y < 1 + x; y++)
		{
			scale.SetToScale(6 + leavesSwayX, 6 + leavesSwayX, 0);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(-20 + y * 5, 33 - x * 4, 4);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
		}
	}

	// ** -------------------------------------------------end of branches of trees------------------------------------------------- **

	/// -------------------------------------------------end of tree------------------------------------------------- /// 

	// -------------------------------------------------start of TINY TREES-------------------------------------------------//
	float smallTreeX = - 40;
	for (int i = 0; i < 10; i++)
	{
		smallTreeX += 8;
		// ** small tree trunk
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BROWN]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		if (i % 2 == 0)
		{
			scale.SetToScale(2, 13, 0);
			translate.SetToTranslation(smallTreeX, -7, -2);
		}
		else
		{
			scale.SetToScale(2, 10, 0);
			translate.SetToTranslation(smallTreeX, -10, -2);
		}
		rotate.SetToRotation(0, 0, 0, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		// some leaves

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GREEN]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		for (int x = 2; x > 0; x--) // one whole bunch of leaves
		{
			for (int y = 0; y < 3; y++)
			{
				if (i % 2 == 0)
				{
					scale.SetToScale(2.5, 2.5, 0);
					translate.SetToTranslation(smallTreeX - 3 + y * 2, 6 - x * 2, -1);
				}
				else
				{
					scale.SetToScale(1.5, 1.5, 0);
					translate.SetToTranslation(smallTreeX - 3 + y * 2, 3 - x * 2, -1);
				}
				rotate.SetToRotation(0, 0, 0, 1);
				model = translate * rotate * scale;
				MVP = projection * view * model;
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

				glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
			}
		}
	}
	// -------------------------------------------------end of small trees-------------------------------------------------//

	// -------------------------------------------------start of boat -------------------------------------------------//

	float boatX = 23, boatY = -11 - boatTranslateX/20;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RTRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(2*boatScaling , 1*boatScaling , 0);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(boatX - 8 * boatScaling + boatTranslateX, boatY + 1 * boatScaling, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(-2 * boatScaling, 1 * boatScaling, 0);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(boatX + 2 * boatScaling + boatTranslateX, boatY + 1 * boatScaling, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,0,0);

	scale.SetToScale(6 * boatScaling, 2 * boatScaling, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(boatX + boatTranslateX, boatY, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(6 * boatScaling, 2 * boatScaling, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(boatX + boatTranslateX, boatY + 2 * boatScaling, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(4 * boatScaling, 1.5*boatScaling, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(boatX - 1 * boatScaling + boatTranslateX, boatY + 2 * boatScaling, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RED]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(4 * boatScaling, 1.5*boatScaling, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(boatX - 3 * boatScaling + boatTranslateX, boatY + 5 * boatScaling, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	// -------------------------------------------------waves-------------------------------------------------//

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLUE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
	
	for (int i = 0; i < 8; ++i)
	{
		float scaling;
		if (boatStop == true)
		{
			scaling = i*0.1;
		}
		else
		{
			scaling = (7-i)*0.1;
		}

		scale.SetToScale(1+scaling, 1+ scaling, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(13 + i * 2 + boatTranslateX + wavesSwayX, -11 - wavesSwayY - boatTranslateX/20, 3);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
	}

	/// -------------------------------------------------end of boat -------------------------------------------------//

	// -------------------------------------------------flower-------------------------------------------------//
	float flowerX, flowerY;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			flowerX = 24;
			flowerY = -25;
		}
		else if (i == 1)
		{
			flowerX = 28;
			flowerY = -24;
		}
		else if (i == 2)
		{
			flowerX = 32;
			flowerY = -25;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(0.7, 0.7, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(flowerX, flowerY, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		if (i == 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLUE]);
		}
		else if (i == 1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PINK]);
		}
		else if (i == 2)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RED]);
		}
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		for (int i = 0; i < 8; ++i)
		{
			scale.SetToScale(1, 2, 0);
			rotate.SetToRotation(i * 45, 0, 0, 1);
			translate.SetToTranslation(flowerX, flowerY, 1);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			flowerX = -12;
			flowerY = -21;
		}
		else if (i == 1)
		{
			flowerX = -15;
			flowerY = -22;
		}
		else if (i == 2)
		{
			flowerX = -14;
			flowerY = -18;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(0.7, 0.7, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(flowerX, flowerY, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		if (i == 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
		}
		else if (i == 1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
		}
		else if (i == 2)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ORANGE]);
		}
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		for (int i = 0; i < 8; ++i)
		{
			scale.SetToScale(1, 2, 0);
			rotate.SetToRotation(i * 45, 0, 0, 1);
			translate.SetToTranslation(flowerX, flowerY, 1);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
		}
	}
	// -------------------------------------------------end of flowers-------------------------------------------------//

	// -------------------------------------------------goose-------------------------------------------------//

	float DuckX = -10 + leavesSwayX/2, DuckY = -13;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(1.5, 0.9, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(DuckX, DuckY, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.6, 0.4, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(DuckX + 1, DuckY + 2, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.5, 2, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(DuckX + 1, DuckY, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.2, 0.5, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(DuckX + 1.2, DuckY + 1.8, 4.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.2, 0.6, 0);
	rotate.SetToRotation(-90, 0, 0, 1);
	translate.SetToTranslation(DuckX + 2, DuckY + 1.9, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	// -------------------------------------------------end of goose-------------------------------------------------//

	// -------------------------------------------------rabbits-------------------------------------------------//
	float RabbitX, RabbitY = -20 + wavesSwayX;
	for (int i = 0; i < 2; ++i)
	{
		if (i == 1)
		{
			RabbitX = 5 + leavesSwayX*2;
		}
		else
		{
			RabbitX = 0 + leavesSwayX*2;
		}


		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);


		if (i == 1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
		}
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(2.5, 2.5, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX, RabbitY + 1, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(2, 2, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX, RabbitY + 3, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(1, 3, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX - 0.5, RabbitY + 4, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(1, 3, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 1.7, RabbitY + 4, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(1, 2, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX - 0.5, RabbitY - 2, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(1, 2, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 1.5, RabbitY - 2, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(0.5, 2, 0);
		rotate.SetToRotation(-45, 0, 0, 1);
		translate.SetToTranslation(RabbitX - 3.0, RabbitY + 0, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(0.5, 2, 0);
		rotate.SetToRotation(45, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 3.0, RabbitY + 0.5, 4);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		if (i == 1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
		}
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(0.3, 0.6, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX - 0.5, RabbitY + 3.5, 4.5);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(0.3, 0.6, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 1, RabbitY + 3.5, 4.5);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(1, 0.3, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 0.5, RabbitY + 2.5, 4.5);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PINK]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		scale.SetToScale(0.5, 2, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX - 0.75, RabbitY + 4.5, 4.6);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(0.5, 2, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 1.25, RabbitY + 4.5, 4.6);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

		scale.SetToScale(0.3, 0.3, 0);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(RabbitX + 0.3, RabbitY + 3, 4.6);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
	}
	//-------------------------------------------------end of rabbit -------------------------------------------------//

	//-------------------------------------------------hiding rabbits-------------------------------------------------//

	float RabbitX2, RabbitY2 = -5;

	RabbitX2 = 7;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(1.25, 1.25, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2, RabbitY2 + 0.5, -3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(1, 1, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 - hideRotate / 50, RabbitY2 + 1.5, -3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.5, 1.5, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 - 0.25 - hideRotate / 50, RabbitY2 + 2 + hideRotate/250, -3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.5, 1.5, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 + 0.75 - hideRotate / 50, RabbitY2 + 2 + hideRotate / 250, -3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[YELLOW]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.15, 0.3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 - 0.25 - hideRotate / 50, RabbitY2 + 1.75, -2.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.15, 0.3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 + 0.5 - hideRotate / 50, RabbitY2 + 1.75, -2.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.5, 0.15, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 + 0.25 - hideRotate / 50, RabbitY2 + 1.25, -2.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[PINK]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	scale.SetToScale(0.25, 1, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 - 0.375 - hideRotate / 40, RabbitY2 + 2.25, -2.4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.25, 1, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 + 0.65 - hideRotate / 40, RabbitY2 + 2.25, -2.4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(0.15, 0.15, 0);
	rotate.SetToRotation(hideRotate, 0, 0, 1);
	translate.SetToTranslation(RabbitX2 + 0.15 - hideRotate / 50, RabbitY2 + 1.5, -2.4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
	

	// -------------------------------------------------end of hiding rabbits-------------------------------------------------//

	//------------------------------------------------- butterfly-------------------------------------------------//

	float butterX, butterY;
	for (int x = 0; x < 2; ++x)
	{
		if (x == 0)
		{
			butterX = 20;
			butterY = -20 + butterflyWingSwing;
		}
		else
		{
			butterX = 30;
			butterY = -23 + butterflyWingSwing*1.5;
		}
		for (int i = 0; i < 2; ++i)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
			if (x == 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ORANGE]);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
			}

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

			scale.SetToScale(1, 1.3, 0);
			rotate.SetToRotation(-135 - butterflyWingSwing * 30 + i * 90, 0, 0, 1);

			translate.SetToTranslation(butterX, butterY - i*1.5, 4);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

			scale.SetToScale(0.3, 0.3, 0);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(butterX, butterY - i*1.5, 4.1);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

		}
		for (int i = 0; i < 2; ++i)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
			if (x == 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ORANGE]);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[WHITE_2]);
			}
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

			scale.SetToScale(1, 1.3, 0);
			rotate.SetToRotation(135 + i*-90 + butterflyWingSwing * 30, 0, 0, 1);
			translate.SetToTranslation(butterX + 1.75, butterY - i * 1.5, 4);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_3]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

			scale.SetToScale(0.3, 0.3, 0);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(butterX + 1.75, butterY - i * 1.5, 4.1);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BROWN]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

			scale.SetToScale(0.3, 1.5, 0);
			rotate.SetToRotation(0, 0, 0, 1);
			translate.SetToTranslation(butterX + 0.85, butterY - 0.5, 4.1);
			model = translate * rotate * scale;
			MVP = projection * view * model;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE_2]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[BLACK]);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
			for (int i = 0; i < 2; ++i)
			{
				scale.SetToScale(0.1, 1.5, 0);
				rotate.SetToRotation(45 + i*-90, 0, 0, 1);
				translate.SetToTranslation(butterX + 0.85, butterY + 1, 4.1);
				model = translate * rotate * scale;
				MVP = projection * view * model;
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

				glDrawArrays(GL_TRIANGLE_STRIP, 0, 36); // Starting from vertex 0; 3 vertices = 1 triangle
			}
		}
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Assignment1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

}