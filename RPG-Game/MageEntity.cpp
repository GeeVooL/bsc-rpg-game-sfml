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
    m_hp = 500;
    m_attack = 300;
    m_orgHp = m_hp;
    m_orgAttack = m_attack;
    m_distance = 6;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;
    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
}

MageEntity::MageEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner, int distance)
{
    m_owner = owner;
    m_hp = hp;
    m_attack = attack;
    m_orgHp = orgHp;
    m_orgAttack = orgAttack;
    m_distance = distance;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;
    
    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
    
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
    mageSprite.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    mageSprite.setScale((8.0 / global::size), (8.0 / global::size));
    
    hpBar.setScale((float) m_hp / m_orgHp, 1.0);
    hpBar.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    
    window.draw(hpBar);
    window.draw(mageSprite);
}

bool MageEntity::move(int oldX, int oldY, int newX, int newY, Entity*** map)
{
    if(oldX - 1 <= newX && oldY - 1 <= newY && newX <= oldX + 1 && newY <= oldY + 1)
        return true;
    return false;
}

bool MageEntity::attack(int posX, int posY, int targetX, int targetY, Entity*** map)
{
    for (int i = posX - 1; i <= posX + 1; i++)
    {
        for(int j = posY - 1; j <= posY + 1; j++)
        {
            if(i >= 0 && j >= 0 && i < global::size && j < global::size && !(i == posX && j == posY) && map[i][j] != nullptr)
                return false;
        }
    }
    
    if(sqrt((targetX - posX)*(targetX - posX) + (targetY - posY)*(targetY - posY)) > m_distance)
        return false;
    
    bool att = 0;
    
    if(map[targetX][targetY] != nullptr && map[targetX][targetY]->getOwner() != this->getOwner())
    {
        map[targetX][targetY]->setHP(map[targetX][targetY]->getHP() - m_attack);
        att = 1;
    }
    if(targetX - 1 >= 0 && map[targetX - 1][targetY] != nullptr && map[targetX - 1][targetY]->getOwner() != this->getOwner())
    {
        map[targetX - 1][targetY]->setHP(map[targetX - 1][targetY]->getHP() - m_attack);
        att = 1;
    }
    if(targetX + 1 < global::size && map[targetX + 1][targetY] != nullptr && map[targetX + 1][targetY]->getOwner() != this->getOwner())
    {
        map[targetX + 1][targetY]->setHP(map[targetX + 1][targetY]->getHP() - m_attack);
        att = 1;
    }
    if(targetY - 1 >= 0 && map[targetX][targetY - 1] != nullptr && map[targetX][targetY - 1]->getOwner() != this->getOwner())
    {
        map[targetX][targetY - 1]->setHP(map[targetX][targetY - 1]->getHP() - m_attack);
        att = 1;
    }
    if(targetY + 1 < global::size && map[targetX][targetY + 1] != nullptr && map[targetX][targetY + 1]->getOwner() != this->getOwner())
    {
        map[targetX][targetY + 1]->setHP(map[targetX][targetY + 1]->getHP() - m_attack);
        att = 1;
    }
    
    if(att)
        return true;
    return false;
}

void MageEntity::toJson(nlohmann::json &output, int k)
{
    output[std::to_string(k)]["type"] = "mage";
    output[std::to_string(k)]["hp"] = m_hp;
    output[std::to_string(k)]["orgHp"] = m_orgHp;
    output[std::to_string(k)]["attack"] = m_attack;
    output[std::to_string(k)]["orgAttack"] = m_orgAttack;
    output[std::to_string(k)]["owner"] = m_owner;
    output[std::to_string(k)]["distance"] = m_distance;
}
