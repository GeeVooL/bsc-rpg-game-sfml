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
