#include "World.h"
#include "Visuals.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "BulletEntity.h"
#include <HAPI_lib.h>
#include <map>

int gametick{ 0 };
int fireDelay{ 20 };
float volume{ 0.25 };
//destructor
World::~World()
{
	for (auto& p : w_entityVector)
		delete p;
	
}

void World::LoadLevel()
{
	//creates all required sprites
	if (!w_vis.CreateSprite("Background", "Data\\background.png"))
	{
		HAPI.UserMessage("Missing texture background", "Error");
		return;
	}
	if (!w_vis.CreateSprite("PlayerSprite", "Data\\F5S4.png"))
	{

		HAPI.UserMessage("Missing texture player", "Error");
		return;
	}
	if (!w_vis.CreateSprite("EnemySprite", "Data\\playersprite.tga"))
	{

		HAPI.UserMessage("Missing texture enemy", "Error");
		return;
	}
	if (!w_vis.CreateSprite("Bullet", "Data\\alphaThing.tga"))
	{
		HAPI.UserMessage("Missing texture bullet", "Error");
		return;
	}
}
//creates the entitiy vector
void World::LoadSprites()
{
	for (int u = 0; u < 5; u++)
	{
		EnemyEntity* newEnemy = new EnemyEntity("Data\\playersprite.tga");
		newEnemy->setup();
		w_entityVector.push_back(newEnemy);
	}

	PlayerEntity* newPlayer = new PlayerEntity("Data\\F5S4.png");
	newPlayer->setup();
	w_entityVector.push_back(newPlayer);

	for (int i = 0; i < bulletEndIndex; i++)
	{
		BulletEntity* newBullet = new BulletEntity("Data\\alphaThing.tga");
		newBullet->setIsAlive(false);
		w_entityVector.push_back(newBullet);
	}
}

//for each loop for bullet spawning
void World::SpawnBullet(int X, int Y)
{
	for (auto entity : w_entityVector)
	{
		if ((entity->getIsAlive() == false) && (fireDelay> 20))
		{
			HAPI.PlayStreamedMedia("Data\\WeaponVFX.ogg", volume);
			entity->setPosition(X, Y);
			entity->setIsAlive(true);
			entity->setup();
			entity->Update(w_vis, *this, score);
			fireDelay = 0;
			break;
		}
	}
}
//Allows the game to be restarted from within the player entity class
void World::RestartGame()
{
	score = 0;
	for (auto entity : w_entityVector)
	{
		entity->setPosition(-200, -200);
		entity->setup();
	}
}

//main loop for the game
void World::Run()
{
	
	srand(time(NULL));
	if (!w_vis.Initialise())
	{
		return;
	}
	int BgY = 1125;
	int Bg2Y = 0;
	LoadLevel();
	LoadSprites();
	
	const HAPI_TKeyboardData& keyScan = HAPI.GetKeyboardData();
	while (HAPI.Update())
	{
		//delta time calculation to smooth the game
		float time = clock();
		deltaTime = time - oldTime;
		oldTime = time;
		
		fireDelay += 1;
		
		
			
		w_vis.ClippedRender("Background", 0, BgY);
		w_vis.ClippedRender("Background", 0, Bg2Y);
			
		BgY = BgY +=3;
		Bg2Y = Bg2Y +=3;
		if (BgY >= 1125)
			BgY = 0;
		if (Bg2Y >= 0)
			Bg2Y = -1125;
		std::string playerScore = "Score: " + std::to_string(score);
		HAPI.RenderText(100, 100, HAPI_TColour::WHITE, playerScore, 20, eBold);
		for (Entity* p : w_entityVector)
			p->Update(w_vis, *this, score);
			
		//collision detection loop
		size_t i = 0;
		for (Entity* p : w_entityVector)
		{
			if (p->getIsAlive() == true)
			{
				if (p->getFaction() != Faction::Neutral)
				{
					for (size_t j = i + 1; j < w_entityVector.size(); j++)
					{
						if (p->hasCollided(w_entityVector[i], w_entityVector[j]))
						{

						}
					}
				}
			}
			i++;
		}
			
		
		
		//win condtion and restart system
		HAPI_UserResponse response;
		if (score >= 100) 
		{
			HAPI.UserMessage("You win! Would you like to play again?", "Game over", HAPI_ButtonType::eButtonTypeYesNo, &response);
			if (response == HAPI_UserResponse::eUserResponseYes)
			{
				score = 0;
				for (auto entity : w_entityVector) //for each loops clears entities from the screen, then places them back in their inital position
				{
					entity->setPosition(-200, -200);
					entity->setup();
				}
			}
			else if (response == HAPI_UserResponse::eUserResponseNo)
			{
				HAPI.Close();
			}
			
		}
	}
}
