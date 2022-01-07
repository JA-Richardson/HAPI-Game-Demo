#include "EnemyEntity.h"
#include "World.h"



int count{ 0 };
//initial setup for enemy - possibly needs changing/removing?
void EnemyEntity::setup()
{
	posX = rand() % 1000 + 10;
	posY = -100;
	health = 5;
}

//update function handles enemy health and respawning on death - needs improvement
void EnemyEntity::Update(Visuals &vis, World& w, int& score)
{
	if (health <= 0)
	{
		HAPI.PlayStreamedMedia("Data\\ExplosionVFX.ogg", volume);
		isAlive = false;
	}
	if (isAlive == false)
	{
		score += 5;
		posX = rand() % 1000 + 10;
		posY = -100;
		health = 5;
		isAlive = true;
	}
	else if (isAlive)
	{
		//moves enemies on a tick - need to replace with vector movement and interpolation at some point
		renderEntity(vis);
		if (count > 5)
		{
			posY += 0.5 * w.getDeltaTime();
			count = 0;
		}
		else if (posY > 1130)
		{
			posX = rand() % 1000 + 10;
			posY = -100;
		}
		else
		{
			count++;
		}	
	}
}

//only allows enemy to render if it is alive
void EnemyEntity::renderEntity(Visuals& vis)
{
	if (isAlive == false)
	{
		return;
	}
	vis.ClippedRender("EnemySprite", posX, posY);
}


