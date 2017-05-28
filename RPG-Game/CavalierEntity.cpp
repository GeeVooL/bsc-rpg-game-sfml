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
