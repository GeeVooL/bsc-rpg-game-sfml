//
//  WarriorEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "WarriorEntity.hpp"

WarriorEntity::WarriorEntity(bool owner)
{
    m_owner = owner;
}

void WarriorEntity::draw(unsigned int i, unsigned int j, sf::Texture &army, sf::RenderWindow &window)
{
    sf::Sprite warriorSprite;
    warriorSprite.setTexture(army);
    if(m_owner == global::ORANGE)
    {
        warriorSprite.setTextureRect(sf::IntRect(100, 100, 100, 100));
    }
    else
    {
        warriorSprite.setTextureRect(sf::IntRect(100, 300, 100, 100));
    }
    warriorSprite.setPosition(i * 100, j * 100);
    window.draw(warriorSprite);
}
