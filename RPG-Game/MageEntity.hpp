//
//  MageEntity.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef MageEntity_hpp
#define MageEntity_hpp

#include "Entity.hpp"
#include "Game.hpp"
#include <cmath>

class MageEntity : public Entity
{
public:
    MageEntity(bool owner);
    MageEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner, int distance);
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) override;
    virtual bool move(int oldX, int oldY, int newX, int newY, Entity*** map) override;
    virtual bool attack(int posX, int posY, int targetX, int targetY, Entity*** map) override;
    virtual void toJson(nlohmann::json &output, int k) override;
private:
    int m_distance;
};

#endif /* MageEntity_hpp */
