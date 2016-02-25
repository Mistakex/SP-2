#include "Assignment3.h"



void Assignment3::Scene1Updates(double dt)
{
	//////////////////Astronaut//////////////////
	if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = false;
		debounceUI.TimeCountDown(dt);
		if (Application::IsKeyPressed(VK_DOWN) && debounceUI.GetTimeNow() <=0)
		{
			if (AstroCursor != (NUM_OPTIONS -1))
			{
				AstroCursor++;
			}
			else
			{
				AstroCursor = 0;
			}
			debounceUI.resetTime();
		}
		if (Application::IsKeyPressed(VK_UP) && debounceUI.GetTimeNow() <= 0)
		{
			if (AstroCursor != 0)
			{
				AstroCursor--;
			}
			else
			{
				AstroCursor = NUM_OPTIONS - 1;
			}
			debounceUI.resetTime();
		}
		if (Application::IsKeyPressed(VK_RETURN) && debounceUI.GetTimeNow() <= 0)
		{
			if (!a.errorWindow)
			{
				switch (AstroCursor)
				{
				case(OPT_BACK_TO_MAIN) :
					gameState = GS_MAIN;
					debounceUI.resetTime();
					break;
				case(OPT_UP_PISTOL) :
					a.UpgradeWeapon(pistol, player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;
				case(OPT_UP_RIFLE) :
					a.UpgradeWeapon(SniperRifle, player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;
				}
			}
			else
			{
				a.errorWindow = false;
				debounceUI.resetTime();
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