//
//  ArcherEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "ArcherEntity.hpp"

ArcherEntity::ArcherEntity(bool owner)
{
    m_owner = owner;
    m_hp = 1000;
    m_attack = 1000;
    m_orgHp = m_hp;
}

void ArcherEntity::draw(unsigned int i, unsigned int j, sf::Texture &army, sf::RenderWindow &window)
{
    sf::Sprite archerSprite;
    archerSprite.setTexture(army);
    if(m_owner == global::ORANGE)
    {
        archerSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    }
    else
    {
        archerSprite.setTextureRect(sf::IntRect(0, 200, 100, 100));
    }
    archerSprite.setPosition(i * 100, j * 100);
    window.draw(archerSprite);
    
}

bool ArcherEntity::move(int oldX, int oldY, int newX, int newY)
{
    if(oldX - 1 <= newX && oldY - 1 <= newY && newX <= oldX + 1 && newY <= oldY + 1)
        return true;
    return false;
}

bool ArcherEntity::attack(int x, int y, Entity*** map)
{
    if(map[x][y] != nullptr && map[x][y]->getOwner() != this->getOwner())
    {
        map[x][y]->setHP(map[x][y]->getHP() - m_attack);
    }
}
