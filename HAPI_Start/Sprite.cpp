#include "Sprite.h"

#include <unordered_map>

//loads sprite from file
bool Sprite::Load(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &s_texture, s_textureWidth, s_textureHeight))
	{
		return false;
	}
    return true;
}

Sprite::~Sprite()
{
	delete[]s_texture;
}

//renders the background - scrolling added in world.cpp, needs to be moved here and improved so less noticeable 
void Sprite::RenderBG(BYTE* screen, int width,  int posX, int posY)
{
	BYTE* tempTexture{ s_texture };
	BYTE* tempScreen{ screen + (posX + posY * (size_t)width) * 4 };
	int endOfLineScreenOffset = (width - s_textureWidth) * 4;
	
		for (int height = 0; height < s_textureHeight; height++)
		{
			for (int width = 0; width < s_textureWidth; width++)
			{
				
				memcpy(tempScreen, tempTexture, 4);
				tempTexture += 4;
				tempScreen += 4;
			}
			tempScreen += endOfLineScreenOffset;
		}
}

//void Sprite::RenderPlayer(BYTE* screen, int width, int posX, int posY)
//{
//	BYTE* texPnter = s_texture;
//	BYTE* screenPnter = { screen + ((size_t)posX + (size_t)posY * (size_t)width) * 4 };
//	int endOfLineScreenOffset = (width - s_textureWidth) * 4;
//
//	for (int x = 0; x < s_textureWidth; x++)
//	{
//		for (int y = 0; y < s_textureHeight; y++)
//		{
//			BYTE red = texPnter[0];
//			BYTE green = texPnter[1];
//			BYTE blue = texPnter[2];
//			BYTE alpha = texPnter[3];
//			if (alpha == 255)
//			{
//				memcpy(screenPnter, texPnter, 4);
//			}
//			else if (alpha > 0)
//			{
//				float mod = alpha / 255.0f;
//				screenPnter[0] = (BYTE)(mod * red + (1.0f - mod) * screenPnter[0]);
//				screenPnter[1] = (BYTE)(mod * green + (1.0f - mod) * screenPnter[1]);
//				screenPnter[2] = (BYTE)(mod * blue + (1.0f - mod) * screenPnter[2]);
//			}
//			texPnter += 4;
//			screenPnter += 4;
//		}
//		screenPnter += endOfLineScreenOffset;
//	}
//}

//renders sprites with clipping
void Sprite::ClippedRender(BYTE* screen, int screenWidth, int screenHeight, int posX, int posY)
{
	Border screenBorder(0, screenWidth, 0, screenHeight);
	Border textureBorder(0, s_textureWidth, 0, s_textureHeight);
	Border clippedRect(textureBorder);
	clippedRect.Translate(posX, posY);
	clippedRect.ClipTo(screenBorder);
	clippedRect.Translate(-posX, -posY);
	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;
	BYTE* clipScreenPnter = screen + ((size_t)posX + (size_t)posY * (size_t)screenBorder.Width()) * 4;
	BYTE* clipTexPnter = s_texture + ((size_t)clippedRect.left + (size_t)clippedRect.top * (size_t)textureBorder.Width()) * 4;
	int endOfLineOffset = (screenBorder.Width() - clippedRect.Width()) * 4;
	int TextureOffset = (textureBorder.Width() - clippedRect.Width()) * 4;
	for (int height = 0; height < clippedRect.Height(); height++)
	{
		for (int width = 0; width < clippedRect.Width(); width++)
		{
			BYTE red = clipTexPnter[0];
			BYTE green = clipTexPnter[1];
			BYTE blue = clipTexPnter[2];
			BYTE alpha = clipTexPnter[3];
			if (alpha == 255)
			{
				memcpy(clipScreenPnter, clipTexPnter, 4);
			}
			else if (alpha > 0)
			{
				float mod = alpha / 255.0f;
				clipScreenPnter[0] = (BYTE)(mod * red + (1.0f - mod) * clipScreenPnter[0]);
				clipScreenPnter[1] = (BYTE)(mod * green + (1.0f - mod) * clipScreenPnter[1]);
				clipScreenPnter[2] = (BYTE)(mod * blue + (1.0f - mod) * clipScreenPnter[2]);
			}
			clipTexPnter += 4;
			clipScreenPnter += 4;
		}
		clipTexPnter += TextureOffset;
		clipScreenPnter += endOfLineOffset;
	}
}

//gets the border of a sprite for collision detection
Border Sprite::getSpriteBorder(const std::string& filename, float posX, float posY)
{
	Load(filename);
	Border textureBorder(0, s_textureWidth -15, 0, s_textureHeight-15);
	textureBorder.Translate(posX, posY);
	
	return textureBorder;
}


