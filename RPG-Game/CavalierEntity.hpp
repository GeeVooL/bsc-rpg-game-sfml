//
//  CavalierEntity.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef CavalierEntity_hpp
#define CavalierEntity_hpp

#include "Entity.hpp"
#include "Game.hpp"

class CavalierEntity : public Entity
{
public:
    CavalierEntity(bool owner);
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) override;
    virtual bool move(int oldX, int oldY, int newX, int newY, Entity*** map) override;
    virtual bool attack(int posX, int posY, int targetX, int targetY, Entity*** map) override;
};
#endif /* CavalierEntity_hpp */
