#pragma once
#include <vector>
#include "Visuals.h"
class Visuals;
class Entity;
class BulletEntity;

class World
{
private:
	void LoadLevel();
	int score{ 0 };
	void LoadSprites();


	size_t bulletStartIndex{ 0 };
	size_t bulletEndIndex{ 20 };

	Visuals w_vis;
	std::vector<Entity*> w_entityVector;
	std::vector<BulletEntity*> bulletVec;
	
	
public:
	void Run();
	~World();
	void SpawnBullet(int X, int Y);
	void RestartGame();
};

