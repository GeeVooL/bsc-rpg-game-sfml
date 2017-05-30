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
    m_hp = 850;
    m_attack = 200;
    m_orgHp = m_hp;
    m_orgAttack = m_attack;
    
    if(m_owner == global::ORANGE)
        global::orangeAmount++;
    else
        global::greenAmount++;

    hpBar.setSize(sf::Vector2f(100 * 8.0 / global::size, 10));
    hpBar.setFillColor(sf::Color(0, 220, 0));
}

CavalierEntity::CavalierEntity(int hp, unsigned orgHp, unsigned attack, unsigned orgAttack, bool owner)
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
    cavalierSprite.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    cavalierSprite.setScale((8.0 / global::size), (8.0 / global::size));
    
    hpBar.setScale((float) m_hp / m_orgHp, 1.0);
    hpBar.setPosition(i * (global::W_WIDTH / global::size), j * (global::W_WIDTH / global::size));
    
    window.draw(hpBar);
    window.draw(cavalierSprite);
}

bool CavalierEntity::move(int oldX, int oldY, int newX, int newY, Entity*** map)
{
    //Only in line
    
    if(newX <= oldX + 3 && newX >= oldX - 3 && newY == oldY)
    {
        if(oldX < newX)
            for(int i = oldX + 1; i <= newX; i++)
            {
                if(map[i][oldY] != nullptr)
                    return false;
            }
        else
            for(int i = newX; i < oldX; i++)
            {
                if(map[i][oldY] != nullptr)
                    return false;
            }
        m_attack += abs(oldX - newX) * 50;
        return true;
    }
    else if (newY <= oldY + 3 && newY >= oldY - 3 && oldX == newX)
    {
        if(oldY < newY)
            for(int i = oldY + 1; i <= newY; i++)
            {
                if(map[oldX][i] != nullptr)
                    return false;
            }
        else
            for(int i = newY; i < oldY; i++)
            {
                if(map[oldX][i] != nullptr)
                    return false;
            }
        m_attack += abs(oldY - newY) * 50;
        return true;
    }
    
    return false;
}

bool CavalierEntity::attack(int posX, int posY, int targetX, int targetY, Entity*** map)
{
    if(map[targetX][targetY] != nullptr && map[targetX][targetY]->getOwner() != this->getOwner() && posX - 1 <= targetX && posY - 1 <= targetY && targetX <= posX + 1 && targetY <= posY + 1)
    {
        map[targetX][targetY]->setHP(map[targetX][targetY]->getHP() - m_attack);
        return true;
    }
    return false;
}

void CavalierEntity::toJson(nlohmann::json &output, int k)
{
    output[std::to_string(k)]["type"] = "cavalier";
    output[std::to_string(k)]["hp"] = m_hp;
    output[std::to_string(k)]["orgHp"] = m_orgHp;
    output[std::to_string(k)]["attack"] = m_attack;
    output[std::to_string(k)]["orgAttack"] = m_orgAttack;
    output[std::to_string(k)]["owner"] = m_owner;
}
