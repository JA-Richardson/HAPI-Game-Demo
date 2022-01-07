#pragma once

#include "HAPI_lib.h"
#include <unordered_map>
using namespace HAPISPACE;
class Sprite;

class Visuals
{
private:
	int v_screenWidth{ 1125 };
	int v_screenHeight{1125};
	BYTE* vScreen{ nullptr };
	
public:
	~Visuals();
	bool Initialise();
	bool CreateSprite(const std::string& spriteName, const std::string& filename);
	void RenderSpriteBG(const std::string& spriteName, int posX, int posY);
	//void RenderSpritePlayer(const std::string& spriteName, int posX, int posY);
	void ClippedRender(const std::string& spriteName, int posX, int posY);
	std::unordered_map<std::string, Sprite*> v_spriteMap;
	
	
	std::unordered_map<std::string, Sprite*> Visuals::getMap()
	{
		return v_spriteMap;
	}
};

