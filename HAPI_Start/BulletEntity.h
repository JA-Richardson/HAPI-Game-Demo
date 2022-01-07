#pragma once
#include "Entity.h"
class BulletEntity :
    public Entity
{
private:
public:
    BulletEntity(std::string filename) : Entity(filename) {};
    void Update(Visuals& vis, World& w, int& score) override final;
    void renderEntity(Visuals& vis);
    void setup() override final;
  
    Faction getFaction() const override { return Faction::Player; }
};

