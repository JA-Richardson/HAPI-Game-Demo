#include "BulletEntity.h"
#include "World.h"

void BulletEntity::Update(Visuals& vis, World& w, int& score)
{
	
	renderEntity(vis);
	posY -= 1 * w.getDeltaTime();
}

//stops entity rendering when killed
void BulletEntity::renderEntity(Visuals& vis)
{
	if (health <= 0)
	{
		isAlive = false;
	}
	if (posY < 0)
	{
		isAlive = false;
	}
	if (isAlive == false)
	{
		return;
	}
	vis.ClippedRender("Bullet", posX, posY);
}

void BulletEntity::setup()
{
	health = 1;
}


