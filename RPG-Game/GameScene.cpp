//
//  GameScene.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "GameScene.hpp"


GameScene::GameScene() : bar(sf::Vector2f(global::W_WIDTH, 200))
{
    backgroundTile.loadFromFile(resourcePath() + "grassTile.png");
    backgroundTile.setRepeated(true);

    bar.setPosition(0, global::W_HEIGHT-200);
    bar.setFillColor(sf::Color(133, 103, 39));
    
    nextTurnButton.loadFromFile(resourcePath() + "nextTurnButton.png");
    
    army.loadFromFile(resourcePath() + "army.png");
    
    map = new Entity**[global::size];
    for (int i = 0; i < global::size; ++i)
    {
        map[i] = new Entity*[global::size];
    }
    
    for(int i = 0; i < global::size; i++)
    {
        for(int j = 0; j < global::size; j++)
        {
            map[i][j] = nullptr;
        }
    }
    
    // Init army
    map[0][0] = new ArcherEntity(global::ORANGE);
    map[0][2] = new WarriorEntity(global::ORANGE);
    map[0][3] = new KnightEntity(global::ORANGE);
    map[0][4] = new CavalierEntity(global::ORANGE);
    map[0][6] = new MageEntity(global::ORANGE);
    
    map[global::size - 1][6] = new ArcherEntity(global::GREEN);
    map[global::size - 1][4] = new WarriorEntity(global::GREEN);
    map[global::size - 1][3] = new KnightEntity(global::GREEN);
    map[global::size - 1][2] = new CavalierEntity(global::GREEN);
    map[global::size - 1][0] = new MageEntity(global::GREEN);
}

GameScene::~GameScene()
{
    for(int i = 0; i < global::size; i++)
    {
        for(int j = 0; j < global::size; j++)
        {
            if(map[i][j] != nullptr)
                delete map[i][j];
        }
    }
    
    for (int i = 0; i < global::size; ++i)
    {
        delete [] map[i];
    }
    delete [] map;

}

void GameScene::render(sf::RenderWindow &window)
{
    drawBackground(window);
    drawFields(window);
    drawMenu(window);
    drawMap(window);
}

void GameScene::drawBackground(sf::RenderWindow &window)
{
    sf::Sprite background(backgroundTile);
    background.setTextureRect(sf::IntRect(0, 0, global::W_WIDTH, global::W_HEIGHT - 200));
    window.draw(background);
    
    window.draw(bar);
}

void GameScene::drawMenu(sf::RenderWindow &window)
{
    sf::Sprite nextTurnSprite(nextTurnButton);
    nextTurnSprite.setOrigin(175 / 2.0, 75 / 2.0);
    nextTurnSprite.setPosition(global::W_WIDTH / 4.0 * 3.0, global::W_HEIGHT - 200 + (200 / 2.0));
    window.draw(nextTurnSprite);
}

void GameScene::drawFields(sf::RenderWindow &window)
{
    for(int i = 1; i <= (global::size) - 1; i++)
    {
        sf::RectangleShape lineY(sf::Vector2f(4, global::W_HEIGHT - 200));
        lineY.setPosition((float)(global::W_WIDTH / global::size) * i, 0);
        lineY.setFillColor(sf::Color(0,0,0));
        window.draw(lineY);
    }
    
    for(int i = 1; i <= (global::size) - 1; i++)
    {
        sf::RectangleShape lineX(sf::Vector2f(global::W_WIDTH, 4));
        lineX.setPosition(0, ((float)(global::W_HEIGHT - 200) / global::size) * i);
        lineX.setFillColor(sf::Color(0,0,0));
        window.draw(lineX);
    }
}

void GameScene::drawMap(sf::RenderWindow &window)
{
    for(int i = 0; i < global::size; i++)
    {
        for(int j = 0; j < global::size; j++)
        {
            if(map[i][j] != nullptr)
                map[i][j]->draw(i, j, army, window);
        }
    }
}

Entity*** GameScene::getMap()
{
    return map;
}
