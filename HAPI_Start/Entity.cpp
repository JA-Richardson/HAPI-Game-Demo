#include "Entity.h"
#include "Sprite.h"
#include "Border.h"
#include "Visuals.h"
#include <memory>
#include <map>
#include "World.h"

//detects collision between two entities and deals with basic health reduction - needs optimising
bool Entity::hasCollided(Entity* other, Entity* object)
{
	Sprite player;
	Sprite enemy;
	Border thisSprite;
	Border otherSprite;
	
	thisSprite = player.getSpriteBorder(other->filename, other->posX, other->posY);
	otherSprite = enemy.getSpriteBorder(object->filename, object->posX, object->posY);

	if (other->getFaction() != object->getFaction())
	{
		if (other->isAlive && object->isAlive)
		{
			if ((thisSprite.right < otherSprite.left || thisSprite.left > otherSprite.right) || (thisSprite.bottom < otherSprite.top || thisSprite.top > otherSprite.bottom))
			{
				return false;
			}
			else
			{
				std::cout << "collision" << std::endl;
				other->health -= 10;
				object->health -= 10;
				
				return true;
			}
		}
		
	}
	else if (other->getFaction() == object->getFaction())
	{
		return false;
	}
	else
		return false;
}

void Entity::setIsAlive(bool isActive)
{
	isAlive = isActive;
	isActive = true;
}

//sets position using the position of the entity that calls the function
void Entity::setPosition(int X, int Y)
{
	posX = X;
	posY = Y;
}
