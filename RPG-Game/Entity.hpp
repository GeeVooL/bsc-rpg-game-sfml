//
//  Entity.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual ~Entity() {};
    unsigned getHP();
    void setHP(unsigned hp);
    unsigned getAttack();
    unsigned getRange();
    bool getOwner();
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) = 0;
    virtual bool move(int oldX, int oldY, int newX, int newY) = 0;
    virtual bool attack(int x, int y, Entity*** map) = 0;
protected:
    unsigned m_hp;
    unsigned m_orgHp;
    unsigned m_attack;
    bool m_owner;
    
};

#endif /* Entity_hpp */
