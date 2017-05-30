//
//  WarriorEntity.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef WarriorEntity_hpp
#define WarriorEntity_hpp

#include "Entity.hpp"
#include "Game.hpp"

class WarriorEntity : public Entity
{
public:
    WarriorEntity(bool owner);
    WarriorEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner);
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) override;
    virtual bool move(int oldX, int oldY, int newX, int newY, Entity*** map) override;
    virtual bool attack(int posX, int posY, int targetX, int targetY, Entity*** map) override;
    virtual void toJson(nlohmann::json &output, int k) override;
};

#endif /* WarriorEntity_hpp */
