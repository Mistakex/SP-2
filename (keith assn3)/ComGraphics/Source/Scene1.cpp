#include "Assignment3.h"



void Assignment3::Scene1Updates(double dt)
{
	//////////////////Astronaut//////////////////
	if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = false;
		if (Application::IsKeyPressed(VK_DOWN))
		{
			if (AstroCursor != (NUM_OPTIONS -1))
			{
				AstroCursor++;
			}
			else
			{
				AstroCursor = 0;
			}
		}
		if (Application::IsKeyPressed(VK_UP))
		{
			if (AstroCursor != 0)
			{
				AstroCursor--;
			}
			else
			{
				AstroCursor = NUM_OPTIONS - 1;
			}
		}
		if (Application::IsKeyPressed(VK_RETURN))
		{
			switch (AstroCursor)
			{
			case(OPT_UP_PISTOL) :
				a.UpgradeWeapon(pistol, player);
				gameState = GS_MAIN;
				break;
			case(OPT_UP_RIFLE) :
				a.UpgradeWeapon(SniperRifle, player);
				gameState = GS_MAIN;
				break;
			}
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

void Assignment3::RenderScene1UI()
{
	if (f.getMagnitude(camera.position) <= 7.5f)
	{
		if (isCaptured == false)
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Capturing Flag...", Color(0, 1, 0), 5, 6, 10);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Flag Captured!", Color(0, 1, 0), 5, 6, 10);
			modelStack.PopMatrix();
		}
	}
}