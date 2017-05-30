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
    m_hp = 1000;
    m_attack = 350;
    m_orgHp = m_hp;
    m_orgAttack = m_attack;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;

    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
}

WarriorEntity::WarriorEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner)
{
    m_owner = owner;
    m_hp = hp;
    m_attack = attack;
    m_orgHp = orgHp;
    m_orgAttack = orgAttack;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;
    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
    
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
    warriorSprite.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    warriorSprite.setScale((8.0 / global::size), (8.0 / global::size));
    
    hpBar.setScale((float) m_hp / m_orgHp, 1.0);
    hpBar.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    
    window.draw(hpBar);
    window.draw(warriorSprite);
}

bool WarriorEntity::move(int oldX, int oldY, int newX, int newY, Entity*** map)
{
    if(oldX - 1 <= newX && oldY - 1 <= newY && newX <= oldX + 1 && newY <= oldY + 1)
        return true;
    return false;
}

bool WarriorEntity::attack(int posX, int posY, int targetX, int targetY, Entity*** map)
{
    if(map[targetX][targetY] != nullptr && map[targetX][targetY]->getOwner() != this->getOwner() && posX - 1 <= targetX && posY - 1 <= targetY && targetX <= posX + 1 && targetY <= posY + 1)
    {
        map[targetX][targetY]->setHP(map[targetX][targetY]->getHP() - m_attack);
        return true;
    }
    return false;
}

void WarriorEntity::toJson(nlohmann::json &output, int k)
{
    output[std::to_string(k)]["type"] = "warrior";
    output[std::to_string(k)]["hp"] = m_hp;
    output[std::to_string(k)]["orgHp"] = m_orgHp;
    output[std::to_string(k)]["attack"] = m_attack;
    output[std::to_string(k)]["orgAttack"] = m_orgAttack;
    output[std::to_string(k)]["owner"] = m_owner;
}
