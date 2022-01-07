#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
private:
    float cathetus(float speed);
public:
   PlayerEntity(std::string filename) : Entity(filename) {};
    void Update(Visuals &vis, World& w, int& score) override final;
    Faction getFaction() const override { return Faction::Player; }
    void setup() override final;
    
};

