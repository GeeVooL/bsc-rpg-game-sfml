//
//  Entity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "Entity.hpp"

unsigned Entity::getHP()
{
    return m_hp;
}

unsigned Entity::getRange()
{
    return m_range;
}

unsigned Entity::getAttack()
{
    return m_attack;
}

unsigned Entity::getDistance()
{
    return m_distance;
}

bool Entity::getOwner()
{
    return m_owner;
}
