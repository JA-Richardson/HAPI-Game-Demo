#pragma once
#include "HAPI_lib.h"
#include "Border.h"
#include <unordered_map>
using namespace HAPISPACE;
class Sprite
{
private:
	BYTE* s_texture{ nullptr };
	int s_textureWidth;
	int	s_textureHeight;
public:
	bool Load(const std::string& filename );
	void RenderBG(BYTE* screen, int width,  int posX, int posY);
	/*void RenderPlayer(BYTE* screen, int width, int posX, int posY);*/
	void ClippedRender(BYTE* screen, int screenWidth, int screenHeight, int posX, int posY);
	~Sprite();
};

