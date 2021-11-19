//Andrew Richardson W9383619
/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file

	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI please see the Reference folder in the HAPI sub-directory
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <Windows.h>
#include <math.h>
#include <cmath>
#include "Visuals.h"
#include "Sprite.h"
#include <unordered_map>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

//unsigned int offset = (x + y * width) * 4; // Remember This

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

float posX{ 100.0f };
float posY{ 100.0f };


//code for equalising diagonal movement speed
float cathetus(float speed)
{
	float speedSquared = pow(speed, 2);
	return sqrt(speedSquared / 2);
}

void HAPI_Main()
{
	Visuals vis;

	if (!vis.Initialise())
		return;

	const HAPI_TKeyboardData& keyScan = HAPI.GetKeyboardData();
	const HAPI_TControllerData& inputScan = HAPI.GetControllerData(0);

	float speed{ 2.0f };
	if (!vis.CreateSprite("Background", "Data\\background.tga"))
	{
		HAPI.UserMessage("Missing texture background", "Error");
		return;
	}
	if (!vis.CreateSprite("PlayerSprite", "Data\\alphaThing.tga"))
	{

		HAPI.UserMessage("Missing texture player", "Error");
		return;
	}
	if (!vis.CreateSprite("TestSprite1", "Data\\playerSprite.tga"))
	{

		HAPI.UserMessage("Missing texture test1", "Error");
		return;
	}
	
	

	while (HAPI.Update())
	{
		const HAPI_TControllerData& inputScan = HAPI.GetControllerData(0);
	
		vis.RenderSpriteBG("Background", 0, 0);
		/*vis.ClippedRender("TestSprite1", -20, 500);
		vis.ClippedRender("TestSprite1", 1100, 700);
		vis.ClippedRender("TestSprite1", 500, 1090);
		vis.ClippedRender("TestSprite1", -20, -20);
		vis.ClippedRender("TestSprite1", -20, 1090);
		vis.ClippedRender("TestSprite1", 1090, 1090);
		vis.ClippedRender("TestSprite1", 1090, -20);
		vis.ClippedRender("TestSprite1", 500, 500);
		vis.ClippedRender("TestSprite1", 800, 1000);
		vis.ClippedRender("TestSprite1", 127, 935);
		vis.ClippedRender("TestSprite1", 83, 109);
		vis.ClippedRender("TestSprite1", 420, 69);
		vis.ClippedRender("TestSprite1", 278, 761);
		vis.ClippedRender("TestSprite1", 600, 382);
		vis.ClippedRender("TestSprite1", 495, 450);
		vis.ClippedRender("TestSprite1", 200, 200);
		vis.ClippedRender("TestSprite1", 1000, 700);
		vis.ClippedRender("TestSprite1", 147, 1000);*/
		vis.ClippedRender("PlayerSprite", posX, posY);
						
		//keyboard input
		if (keyScan.scanCode['S'] && (keyScan.scanCode['D']))//South East
		{
			posY += cathetus(speed);
			posX += cathetus(speed);
		}
		else if (keyScan.scanCode['W'] && (keyScan.scanCode['A']))//North West
		{
			posY -= cathetus(speed);
			posX -= cathetus(speed);
		}
		else if (keyScan.scanCode['W'] && (keyScan.scanCode['D']))//North East
		{
			posY -= cathetus(speed);
			posX += cathetus(speed);
		}
		else if (keyScan.scanCode['S'] && (keyScan.scanCode['A']))//South West
		{
			posY += cathetus(speed);
			posX -= cathetus(speed);
		}
		else if (keyScan.scanCode['W'])//North
		{
			posY -= speed;
		}
		else if (keyScan.scanCode['D'])//East
		{
			posX += speed;
		}
		else if (keyScan.scanCode['S'])//South
		{
			posY += speed;
		}
		else if (keyScan.scanCode['A'])//West
		{
			posX -= speed;
		}
		
		//controller input
		if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000))
		{
			posY -= cathetus(speed);
			posX += cathetus(speed);
		}
		else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000))
		{
			posY += cathetus(speed);
			posX += cathetus(speed);
		}
		else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000))
		{
			posY += cathetus(speed);
			posX -= cathetus(speed);
		}
		else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000))
		{
			posY -= cathetus(speed);
			posX -= cathetus(speed);
		}
		else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			
			posX += speed;
		}
		else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			posX -= speed;
		}
		else if (inputScan.isAttached&& inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
		{
			posY -= speed;

		}
		else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
		{
			posY += speed;
		}

		if ((posX > 350 && posX < 750) && (posY > 350 && posY < 750))
		{
			HAPI.SetControllerRumble(0, 65535, 65535);
		}
		else if (HAPI.SetControllerRumble(0, 0, 0));
	}
	
}