#include "Assignment3.h"

static float SpaceTruckRotation = 0.f;

void Assignment3::Scene1Updates(double dt)
{
	//space truck rotation
	if (SpaceTruckRotation < 360.f)
		SpaceTruckRotation += 10.f * (float)dt;
	else
		SpaceTruckRotation = 0.f;

	//////////////////Astronaut//////////////////
	debounceUI.TimeCountDown(dt);
	if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = false;
		if (((Application::IsKeyPressed('S')) || (Application::IsKeyPressed(VK_DOWN))) && (debounceUI.GetTimeNow() <= 0))
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
		if (((Application::IsKeyPressed('W')) || (Application::IsKeyPressed(VK_UP))) && (debounceUI.GetTimeNow() <= 0))
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
					std::cout << pistol.Damage << std::endl;
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_RIFLE) :
					a.UpgradeWeapon(SniperRifle, player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_TURRET) :
					a.UpgradeTurret(player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_NADE_DMG) :
					a.UpgradeGrenadeDamage(player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_NADE_RANGE) :
					a.UpgradeGrenadeRange(player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_MEDKIT_TICKS) :
					a.UpgradeMedkitTicks(player, medKit);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_UP_MEDKIT_HEAL) :
					a.UpgradeMedkitHeal(player, medKit);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_BUY_HARVESTOR) :
					a.PurchaseHarvestor(player);
					debounceUI.resetTime();
					a.errorWindow = true;
					break;

				case(OPT_BUY_GRENADES) :
					a.PurchaseGrenades(player);
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
	if (Application::IsKeyPressed('E') && gameState == GS_ASTRONAUT_INTERACTION && debounceUI.GetTimeNow() <= 0)
	{
		gameState = GS_MAIN;
		a.errorWindow = false;
		debounceUI.resetTime();
	}
	if (Application::IsKeyPressed('E') && ((getMagnitude(a.GetAstronautPos(), camera.position)) < 3) && debounceUI.GetTimeNow() <= 0)
	{
		gameState = GS_ASTRONAUT_INTERACTION;
		AstroCursor = 0;
		debounceUI.resetTime();
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

	//SPACETRUCK
	modelStack.PushMatrix();
	modelStack.Rotate(-SpaceTruckRotation, 0, 1, 0);
	modelStack.Translate(150,-1,0);
	RenderMesh(meshList[GEO_SPACETRUCK], true);
	modelStack.PopMatrix();

	//SPACESHIP
	if (isCaptured || ship.updateCutscene)
	{
		modelStack.PushMatrix();
		modelStack.Translate(ship.position.x, -1 + ship.position.y, ship.position.z);
		RenderMesh(meshList[GEO_SPACESHIP], true);
		modelStack.PopMatrix();
	}
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
			RenderTextOnScreen(meshList[GEO_TEXT], "Head to the ship!", Color(0, 1, 0), 5, 6, 10);
			modelStack.PopMatrix();
		}
	}
}

void Assignment3::RenderAstronautInteractions()
{
	if (gameState == GS_ASTRONAUT_INTERACTION && !a.errorWindow)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], AstronautOpt[AstroCursor], Color(1, 0, 1), 4.5f, 5, 7);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to exit and 'Enter' to choose", Color(1, 0, 0), 2.5f, 10, 9);
		switch (AstroCursor)
		{
		case(OPT_UP_PISTOL) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(pistol.getUpgradeCost()), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_RIFLE) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(SniperRifle.getUpgradeCost()), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_TURRET) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(a.TurretNewDmg), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_NADE_DMG) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(((a.GrenadeDamage - 100) + 30)), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_NADE_RANGE) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(((a.GrenadeRange - 19) * 10)), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_MEDKIT_TICKS) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(((medKit.MaxTimesHealed) * 10)), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_UP_MEDKIT_HEAL) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(((medKit.HealAmount / 10) * 35)), Color(1, 0, 1), 4.5f, 5, 6);
			break;

		case(OPT_BUY_HARVESTOR) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(50), Color(1, 0, 1), 4, 5.6f, 7);
			RenderTextOnScreen(meshList[GEO_TEXT], "Harvestors Owned: " + std::to_string(a.Harvestor.size()), Color(1, 0, 1), 4, 5.6f, 6);
			break;

		case(OPT_BUY_GRENADES) :
			RenderTextOnScreen(meshList[GEO_TEXT], "Resources Needed: " + std::to_string(30), Color(1, 0, 1), 4, 5.6f, 7);
			RenderTextOnScreen(meshList[GEO_TEXT], "Grenades Owned: " + std::to_string(player.noOfGrenadesHeld), Color(1, 0, 1), 4, 5.6f, 6);
			break;

		default:
			break;
		}
	}

	if (!a.upgradeSuccess && a.errorWindow && !a.enablePurchaseWindow)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Not Enough Resources...", Color(1, 0, 1), 5, 4.5f, 5.7f);
	}

	if (a.upgradeSuccess && a.errorWindow && !a.enablePurchaseWindow)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Upgrade Success!", Color(1, 0, 1), 5, 5.5f, 5.7f);
	}

	if (!a.purchaseSuccess && a.errorWindow && a.enablePurchaseWindow)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Can't hold anymore of this...", Color(1, 0, 1), 4, 5.6f, 7.2f);
	}

	if (a.purchaseSuccess && a.errorWindow && a.enablePurchaseWindow)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Purchase Success!", Color(1, 0, 1), 5, 5.5f, 5.7f);
	}
}