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
    int getHP();
    void setHP(unsigned hp);
    unsigned getAttack();
    void resetAttack();
    unsigned getRange();
    bool getOwner();
    virtual void draw(unsigned i, unsigned j, sf::Texture &army, sf::RenderWindow &window) = 0;
    virtual bool move(int oldX, int oldY, int newX, int newY, Entity*** map) = 0;
    virtual bool attack(int posX, int posY, int targetX, int targetY, Entity*** map) = 0;
protected:
    sf::RectangleShape hpBar;
    
    int m_hp;
    unsigned m_orgHp;
    unsigned m_attack;
    unsigned m_orgAttack;
    bool m_owner;
    
};

#endif /* Entity_hpp */
