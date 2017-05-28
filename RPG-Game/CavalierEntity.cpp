//
//  CavalierEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "CavalierEntity.hpp"

CavalierEntity::CavalierEntity(bool owner)
{
    m_owner = owner;
    m_hp = 1000;
    m_attack = 1000;
    m_orgHp = m_hp;
}

void CavalierEntity::draw(unsigned int i, unsigned int j, sf::Texture &army, sf::RenderWindow &window)
{
    sf::Sprite cavalierSprite;
    cavalierSprite.setTexture(army);
    if(m_owner == global::ORANGE)
    {
        cavalierSprite.setTextureRect(sf::IntRect(200, 0, 100, 100));
    }
    else
    {
        cavalierSprite.setTextureRect(sf::IntRect(200, 200, 100, 100));
    }
    cavalierSprite.setPosition(i * 100, j * 100);
    window.draw(cavalierSprite);
}

bool CavalierEntity::move(int oldX, int oldY, int newX, int newY)
{
    //Only in lines
    if(oldX - 1 <= newX && newX <= oldX + 1 && oldY - 1 <= newY && newY <= oldY + 1)
        return true;
    return false;
}

bool CavalierEntity::attack(int x, int y, Entity*** map)
{
    if(map[x][y] != nullptr && map[x][y]->getOwner() != this->getOwner())
    {
        map[x][y]->setHP(map[x][y]->getHP() - m_attack);
    }
}
