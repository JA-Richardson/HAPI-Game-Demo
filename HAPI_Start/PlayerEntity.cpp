#include "PlayerEntity.h"
#include "BulletEntity.h"
#include "World.h"
//#include <Windows.h>
#include <HAPI_lib.h>
using namespace HAPISPACE;

float speed{ 0.2f };


//stops player moving faster diagonally 
float PlayerEntity::cathetus(float speed)
{
	float speedSquared = pow(speed, 2);
	return sqrt(speedSquared / 2);
}

//sets players initial position and health - possibly needs changing?
void PlayerEntity::setup()
{
	posX = 510.f;
	posY = 510.f;
	health = 20;
	isAlive = true;
	
}

//contains control fuctions for player
void PlayerEntity::Update(Visuals &vis, World& w, int& score)
{
	HAPI_UserResponse response;
	vis.ClippedRender("PlayerSprite", posX, posY);

	const HAPI_TKeyboardData& keyScan = HAPI.GetKeyboardData();
	const HAPI_TControllerData& inputScan = HAPI.GetControllerData(0);
	if (health <= 0)
	{
		HAPI.PlayStreamedMedia("Data\\ExplosionVFX.ogg", volume);
		isAlive = false;
	}
	if (isAlive == false)
	{
		//allows for restarting or exiting of the game if the player dies
		HAPI.UserMessage("PlayerDied! Would you like to play again?", "Game over", HAPI_ButtonType::eButtonTypeYesNo, &response);
		if (response == HAPI_UserResponse::eUserResponseYes)
		{
			w.RestartGame();
		}
		else if (response == HAPI_UserResponse::eUserResponseNo)
		{
			HAPI.Close();
		}
	}

	HAPI.GetTime();
	if (keyScan.scanCode['Q'])
	{
		w.SpawnBullet((posX + 15), (posY));
	}
	if (keyScan.scanCode['S'] && (keyScan.scanCode['D']))//South East
	{
		posY += cathetus(speed * w.getDeltaTime());
		posX += cathetus(speed * w.getDeltaTime());
	}
	else if (keyScan.scanCode['W'] && (keyScan.scanCode['A']))//North West
	{
		posY -= cathetus(speed * w.getDeltaTime());
		posX -= cathetus(speed * w.getDeltaTime());
	}
	else if (keyScan.scanCode['W'] && (keyScan.scanCode['D']))//North East
	{
		posY -= cathetus(speed * w.getDeltaTime());
		posX += cathetus(speed * w.getDeltaTime());
	}
	else if (keyScan.scanCode['S'] && (keyScan.scanCode['A']))//South West
	{
		posY += cathetus(speed * w.getDeltaTime());
		posX -= cathetus(speed * w.getDeltaTime());
	}
	else if (keyScan.scanCode['W'])//North
	{
		posY -= speed * w.getDeltaTime();
	}
	else if (keyScan.scanCode['D'])//East
	{
		posX += speed * w.getDeltaTime();
	}
	else if (keyScan.scanCode['S'])//South
	{
		posY += speed * w.getDeltaTime();
	}
	else if (keyScan.scanCode['A'])//West
	{
		posX -= speed * w.getDeltaTime();
	}
	
	//controller input
	if (inputScan.isAttached && inputScan.digitalButtons[HK_DIGITAL_A])
	{
		w.SpawnBullet((posX+15), (posY));
	}
	if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000))
	{
		posY -= cathetus(speed * w.getDeltaTime());
		posX += cathetus(speed * w.getDeltaTime());
	}
	else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000))
	{
		posY += cathetus(speed * w.getDeltaTime());
		posX += cathetus(speed * w.getDeltaTime());
	}
	else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000))
	{
		posY += cathetus(speed * w.getDeltaTime());
		posX -= cathetus(speed * w.getDeltaTime());
	}
	else if ((inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000) && (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000))
	{
		posY -= cathetus(speed * w.getDeltaTime());
		posX -= cathetus(speed * w.getDeltaTime());
	}
	else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
	{

		posX += speed * w.getDeltaTime();
	}
	else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
	{
		posX -= speed * w.getDeltaTime();
	}
	else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
	{
		posY -= speed * w.getDeltaTime();

	}
	else if (inputScan.isAttached && inputScan.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
	{
		posY += speed * w.getDeltaTime();
	}

	
}


