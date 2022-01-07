#include "Visuals.h"
#include "Sprite.h"
#include <unordered_map>



Visuals::~Visuals()
{
    for (auto& p : v_spriteMap)
        delete p.second;
}

bool Visuals::Initialise()
{
    if (!HAPI.Initialise(v_screenWidth, v_screenHeight))
        return false;
    vScreen = HAPI.GetScreenPointer();
    HAPI.GetFPS();
    HAPI.SetShowFPS(true);
    
    return true;
}

//loads sprites from spritemap and creates an entity
bool Visuals::CreateSprite(const std::string& spriteName, const std::string& filename)
{
    Sprite* newSprite = new Sprite();
    if (!newSprite->Load(filename))
    {
        HAPI.UserMessage("load fail", "Error");
        delete newSprite;
        return false;
    }
    
    v_spriteMap[spriteName] = newSprite;
    return true;
}

void Visuals::RenderSpriteBG(const std::string& spriteName, int posX, int posY)
{
    if (v_spriteMap.find(spriteName) == v_spriteMap.end())
    {
        HAPI.UserMessage("spritemap failure", "Error");
        return;
    }
    v_spriteMap[spriteName]->RenderBG(vScreen, v_screenWidth, posX, posY);
}

//void Visuals::RenderSpritePlayer(const std::string& spriteName, int posX, int posY)
//{
//    if (v_spriteMap.find(spriteName) == v_spriteMap.end())
//    {
//        HAPI.UserMessage("spritemap failure", "Error");
//        return;
//    }
//
//    v_spriteMap[spriteName]->RenderPlayer(vScreen, v_screenWidth, posX, posY);
//}

//loads from spritemap to create an entity with clipping
void Visuals::ClippedRender(const std::string& spriteName, int posX, int posY)
{

    if (v_spriteMap.find(spriteName) == v_spriteMap.end())
    {
        HAPI.UserMessage("spritemap failure", "Error");
        return;
    }

    v_spriteMap[spriteName]->ClippedRender(vScreen, v_screenWidth, v_screenHeight, posX, posY);
}
