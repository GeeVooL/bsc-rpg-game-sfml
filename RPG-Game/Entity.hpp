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
    //virtual void move() = 0;
    //virtual void attack() = 0;
    virtual ~Entity() {};
    unsigned getHP();
    unsigned getAttack();
    unsigned getRange();
    unsigned getDistance();
    bool getOwner();
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) = 0;
    virtual bool move(unsigned oldX, unsigned oldY, unsigned newX, unsigned newY) = 0;
protected:
    unsigned m_distance;
    unsigned m_range;
    unsigned m_hp;
    unsigned m_attack;
    bool m_hasAttacked;
    bool m_owner;
    
};

#endif /* Entity_hpp */
