#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	// Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Enable depth testing and depth buffer
	glEnable(GL_DEPTH_TEST);

	// Use our shader
	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate Buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] =
	{
		-0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] =
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	rotateAngle = 30.0;
	translateX = 1.0;
	scaleAll = 4.0;
}

void Scene2::Update(double dt)
{
	rotateAngle += (float)(40 * dt);
	translateX += (float)(10 * dt);
	scaleAll += (float)(2 * dt);
}

void Scene2::Render()
{
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

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(rotateAngle, 0, 1, 0);
	translate.SetToTranslation(translateX, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	// Render VBO here
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT);

	// Clear color and depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, // Attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3, // Size
		GL_FLOAT, // Type
		GL_TRUE, // Normalized?
		0, // Stride
		0 // Array buffer offset
		);

	glEnableVertexAttribArray(1);
	// 2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX, 10, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(rotateAngle, 1, 0, 0);
	translate.SetToTranslation(translateX, 10, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Scene2::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
