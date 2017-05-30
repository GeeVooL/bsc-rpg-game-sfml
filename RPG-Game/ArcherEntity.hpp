//
//  ArcherEntity.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef ArcherEntity_hpp
#define ArcherEntity_hpp

#include "Entity.hpp"
#include "Game.hpp"

class ArcherEntity : public Entity
{
public:
    ArcherEntity(bool owner);
    ArcherEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner, int distance);
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) override;
    virtual bool move(int oldX, int oldY, int newX, int newY, Entity*** map) override;
    virtual bool attack(int posX, int posY, int targetX, int targetY, Entity*** map) override;
    virtual void toJson(nlohmann::json &output, int k) override;
private:
    int m_distance;
};

#endif /* ArcherEntity_hpp */
