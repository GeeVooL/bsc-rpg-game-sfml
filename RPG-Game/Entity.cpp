//
//  Entity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "Entity.hpp"

int Entity::getHP()
{
    return m_hp;
}

unsigned Entity::getAttack()
{
    return m_attack;
}

bool Entity::getOwner()
{
    return m_owner;
}

void Entity::setHP(unsigned hp)
{
    m_hp = hp;
}

void Entity::resetAttack()
{
    m_attack = m_orgAttack;
}
