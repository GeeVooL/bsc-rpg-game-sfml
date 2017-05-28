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

class MageEntity : public Entity
{
public:
    MageEntity(bool owner);
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) override;
    virtual bool move(int oldX, int oldY, int newX, int newY) override;
    virtual bool attack(int x, int y, Entity*** map) override;
};

#endif /* MageEntity_hpp */
