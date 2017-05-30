//
//  ArcherEntity.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "ArcherEntity.hpp"
#include <cmath>

ArcherEntity::ArcherEntity(bool owner)
{
    m_owner = owner;
    m_hp = 600;
    m_attack = 150;
    m_distance = 5;
    m_orgHp = m_hp;
    m_orgAttack = m_attack;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;
    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
}

ArcherEntity::ArcherEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner, int distance)
{
    m_owner = owner;
    m_hp = hp;
    m_attack = attack;
    m_distance = distance;
    m_orgHp = orgHp;
    m_orgAttack = orgAttack;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;
    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));

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
    archerSprite.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    archerSprite.setScale((8.0 / global::size), (8.0 / global::size));
    
    hpBar.setScale((float) m_hp / m_orgHp, 1.0);
    hpBar.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    
    window.draw(hpBar);
    window.draw(archerSprite);
    
}

bool ArcherEntity::move(int oldX, int oldY, int newX, int newY, Entity*** map)
{
    if(oldX - 1 <= newX && oldY - 1 <= newY && newX <= oldX + 1 && newY <= oldY + 1)
        return true;
    return false;
}

bool ArcherEntity::attack(int posX, int posY, int targetX, int targetY, Entity*** map)
{
    if(map[targetX][targetY] != nullptr && map[targetX][targetY]->getOwner() != this->getOwner() && sqrt((targetX - posX)*(targetX - posX) + (targetY - posY)*(targetY - posY)) <= m_distance)
    {
        map[targetX][targetY]->setHP(map[targetX][targetY]->getHP() - m_attack);
        return true;
    }
    return false;
}

void ArcherEntity::toJson(nlohmann::json &output, int k)
{
    output[std::to_string(k)]["type"] = "archer";
    output[std::to_string(k)]["hp"] = m_hp;
    output[std::to_string(k)]["orgHp"] = m_orgHp;
    output[std::to_string(k)]["attack"] = m_attack;
    output[std::to_string(k)]["orgAttack"] = m_orgAttack;
    output[std::to_string(k)]["owner"] = m_owner;
    output[std::to_string(k)]["distance"] = m_distance;
}
