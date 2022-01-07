#pragma once
#include <vector>
#include "Visuals.h"
#include "Border.h"
#include "Vector2.h"
#include <map>
class World;
enum class Faction
{
	Neutral,
	Player,
	Enemy,

};

class Entity
{
protected:
	std::string SpriteName;
	std::string filename;
	Faction faction{ Faction::Neutral };
	float posX;
	float posY;
	int health;
	bool isAlive{ true };
	float volume{ 0.25f };
private:
public:
	Entity(std::string filename) : filename(filename) {};
	virtual ~Entity() = default;
	virtual void Update(Visuals &vis, World &w, int &score) = 0;
	void renderEntity(Visuals& vis) {};
	virtual Faction getFaction() const = 0;
	virtual void setup() = 0;
	bool hasCollided(Entity* other, Entity* object);
	bool getIsAlive() { return isAlive; };
	void setIsAlive(bool isActive);
	void setPosition(int X, int Y);
};

