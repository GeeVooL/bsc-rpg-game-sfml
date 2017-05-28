//
//  KnightEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "KnightEntity.hpp"

KnightEntity::KnightEntity(bool owner)
{
    m_owner = owner;
}

void KnightEntity::draw(unsigned int i, unsigned int j, sf::Texture &army, sf::RenderWindow &window)
{
    sf::Sprite knightSprite;
    knightSprite.setTexture(army);
    if(m_owner == global::ORANGE)
    {
        knightSprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
    }
    else
    {
        knightSprite.setTextureRect(sf::IntRect(100, 200, 100, 100));
    }
    knightSprite.setPosition(i * 100, j * 100);
    window.draw(knightSprite);
}
