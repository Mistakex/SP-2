#include "Assignment3.h"



void Assignment3::Scene1Updates(double dt)
{
	//////////////////Astronaut//////////////////
	if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = false;
		if (Application::IsKeyPressed('Y'))
		{
			a.UpgradeWeapon(pistol, player);
			gameState = GS_MAIN;
		}
		if (Application::IsKeyPressed('N'))
		{
			gameState = GS_MAIN;
		}
	}

	//Astronaut initiate talking
	if (Application::IsKeyPressed('E') && ((getMagnitude(a.GetAstronautPos(), camera.position)) < 3))
	{
		gameState = GS_ASTRONAUT_INTERACTION;
	}
	////////////////////////////////////////////

	//////////////////Flag//////////////////////
	// flag rising up when get close
	if (f.getMagnitude(camera.position) <= 7.5f)
	{
		if (f.flagIsBlue == true)
		{
			if (f.FlagHeightIncrease(2.5f, dt) >= 2.5f)
			{
				isCaptured = true;
			};
		}
		else if (f.FlagHeightDecrease(0.5f, dt) <= 0.5f)
		{
			f.flagIsBlue = true;
			isCapturing = true;
		}
	}
	else
	{
		isCapturing = false;
	}
	//reset everything
	if (Application::IsKeyPressed('R'))
	{
		f.flagIsBlue = false;
		f.flagheight = 2;
	}
	//////////////////////////////////////////////
}
void Assignment3::Scene1Render()
{
	//POLE
	RenderPole();
	//FLAG
	RenderFlag();
	//ASTRONAUT
	RenderAstronaut();
	//CRATERS;
	RenderCraters();
}