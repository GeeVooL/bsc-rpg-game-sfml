//
//  MageEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "MageEntity.hpp"

MageEntity::MageEntity(bool owner)
{
    m_owner = owner;
    m_hp = 1000;
    m_attack = 1000;
    m_orgHp = m_hp;
}

void MageEntity::draw(unsigned int i, unsigned int j, sf::Texture &army, sf::RenderWindow &window)
{
    sf::Sprite mageSprite;
    mageSprite.setTexture(army);
    if(m_owner == global::ORANGE)
    {
        mageSprite.setTextureRect(sf::IntRect(0, 100, 100, 100));
    }
    else
    {
        mageSprite.setTextureRect(sf::IntRect(0, 300, 100, 100));
    }
    mageSprite.setPosition(i * 100, j * 100);
    window.draw(mageSprite);
}

bool MageEntity::move(int oldX, int oldY, int newX, int newY)
{
    if(oldX - 1 <= newX && oldY - 1 <= newY && newX <= oldX + 1 && newY <= oldY + 1)
        return true;
    return false;
}

bool MageEntity::attack(int x, int y, Entity*** map)
{
    if(map[x][y] != nullptr && map[x][y]->getOwner() != this->getOwner())
    {
        map[x][y]->setHP(map[x][y]->getHP() - m_attack);
    }
}
