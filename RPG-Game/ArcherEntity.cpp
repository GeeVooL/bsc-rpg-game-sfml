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
