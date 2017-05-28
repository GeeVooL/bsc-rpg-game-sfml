//
//  GameScene.hpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "Game.hpp"
#include "Entity.hpp"
#include <vector>
#include <cstdlib>

class GameScene
{
public:
    GameScene();
    ~GameScene();
    void render(sf::RenderWindow &window);
    Entity*** getMap();
    
private:
    void drawBackground(sf::RenderWindow &window);
    void drawFields(sf::RenderWindow &window);
    void drawMenu(sf::RenderWindow &window);
    void drawMap(sf::RenderWindow &window);
    
    sf::Texture backgroundTile;
    sf::RectangleShape bar;
    sf::Texture nextTurnButton;
    sf::Texture saveButton;
    sf::RectangleShape lineY;
    sf::RectangleShape lineX;
    sf::Texture army;
    
    bool m_turn;
    Entity*** map;
};

#endif /* GameScene_hpp */
