//
//  Game.cpp
//  RPG-Game
//
//  Created by Michał Dziewulski on 10.05.2017.
//  Copyright © 2017 Michał Dziewulski. All rights reserved.
//

#include "Game.hpp"

const float global::W_HEIGHT = 1000; // 800 map + 200 bar
const float global::W_WIDTH = 800;
const unsigned global::size = 8;
const bool global::GREEN = 1;
const bool global::ORANGE = 0;
Entity*** map = nullptr;

Game::Game() : bar(sf::Vector2f(global::W_WIDTH, 200))
{
    selected = nullptr;
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

Game::~Game()
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

void Game::run()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(global::W_WIDTH, global::W_HEIGHT), "RPG-Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    // Load a music to play
    //sf::Music music;
    //if (!music.openFromFile(resourcePath() + "themeSong.mp3")) {
    //    return EXIT_FAILURE;
    //}
    
    // Play the music
    //music.play();
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Mouse clicked - left
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(event.mouseButton.y <= global::W_HEIGHT - 200)
                    {
                        int positionX = event.mouseButton.x / 100;
                        int positionY = event.mouseButton.y / 100;
                    
                        if(selected == nullptr && map[positionX][positionY] != nullptr)
                        {
                            if(map[positionX][positionY]->getOwner() == m_turn)
                            {
                                selected = map[positionX][positionY];
                                selectedPosX = positionX;
                                selectedPosY = positionY;
                            }
                        }
                        else
                        {
                            if(map[positionX][positionY] == nullptr && selected->move(selectedPosX, selectedPosY, positionX, positionY))
                            {
                                map[positionX][positionY] = selected;
                                map[selectedPosX][selectedPosY] = nullptr;
                                selected = nullptr;
                            }
                        }
                    
                    }
                    else if (event.mouseButton.x > 512 && event.mouseButton.x < 688 && event.mouseButton.y > 862 && event.mouseButton.y < 938)
                    {
                        m_turn = !m_turn;
                    }
                }
            }
        }
        
        // Clear screen
        window.clear();
        
        // Render scene
        render(window);
        
        // Update the window
        window.display();
    }

}

void Game::render(sf::RenderWindow &window)
{
    drawBackground(window);
    drawFields(window);
    drawMenu(window);
    drawMap(window);
}

void Game::drawBackground(sf::RenderWindow &window)
{
    sf::Sprite background(backgroundTile);
    background.setTextureRect(sf::IntRect(0, 0, global::W_WIDTH, global::W_HEIGHT - 200));
    window.draw(background);
    
    window.draw(bar);
}

void Game::drawMenu(sf::RenderWindow &window)
{
    sf::Sprite nextTurnSprite(nextTurnButton);
    nextTurnSprite.setOrigin(175 / 2.0, 75 / 2.0);
    nextTurnSprite.setPosition(global::W_WIDTH / 4.0 * 3.0, global::W_HEIGHT - 200 + (200 / 2.0));
    window.draw(nextTurnSprite);
}

void Game::drawFields(sf::RenderWindow &window)
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

void Game::drawMap(sf::RenderWindow &window)
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
