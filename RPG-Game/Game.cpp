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
unsigned global::size = 8;
const bool global::GREEN = 1;
const bool global::ORANGE = 0;
unsigned global::greenAmount = 0;
unsigned global::orangeAmount = 0;

Entity*** map = nullptr;

Game::Game() : bar(sf::Vector2f(global::W_WIDTH, 200))
{
    selected = nullptr;
    m_turn = global::ORANGE;
    m_hasMoved = 0;
    m_hasAttacked = 0;
    
    backgroundTile.loadFromFile(resourcePath() + "grassTile.png");
    backgroundTile.setRepeated(true);
    
    bar.setPosition(0, global::W_HEIGHT-200);
    bar.setFillColor(sf::Color(133, 103, 39));
    
    playerTurn.setPosition(global::W_WIDTH / 2.0 - 37.5, (global::W_HEIGHT - 200) + 200 / 2.0 - 37.5);
    playerTurn.setSize(sf::Vector2f(75.0, 75.0));
    playerTurn.setFillColor(sf::Color(255,128,0));
    
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
                int positionX = event.mouseButton.x / (100.0 * 8.0 / global::size);
                int positionY = event.mouseButton.y / (100.0 * 8.0 / global::size);
                
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(event.mouseButton.y <= global::W_HEIGHT - 200)
                    {
                        if(map[positionX][positionY] != nullptr)
                        {
                            if(map[positionX][positionY]->getOwner() == m_turn)
                            {
                                selected = map[positionX][positionY];
                                selectedPosX = positionX;
                                selectedPosY = positionY;
                            }
                        }
                        else if (selected != nullptr)
                        {
                            if(!m_hasMoved && selected->getOwner() == m_turn && map[positionX][positionY] == nullptr && selected->move(selectedPosX, selectedPosY, positionX, positionY, map))
                            {
                                map[positionX][positionY] = selected;
                                map[selectedPosX][selectedPosY] = nullptr;
                                selected = nullptr;
                                m_hasMoved = 1;
                            }
                        }
                    
                    }
                    else if (event.mouseButton.x > 512 && event.mouseButton.x < 688 && event.mouseButton.y > 862 && event.mouseButton.y < 938)
                    {
                        for(int i = 0; i < global::size; i++)
                        {
                            for(int j = 0; j < global::size; j++)
                            {
                                if(map[i][j] != nullptr)
                                {
                                    map[i][j]->resetAttack();
                                }
                            }
                        }
                        
                        m_turn = !m_turn;
                        m_hasMoved = 0;
                        m_hasAttacked = 0;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if(selected != nullptr && !m_hasAttacked && map[positionX][positionY] != selected)
                        if(selected->attack(selectedPosX, selectedPosY, positionX, positionY, map))
                            m_hasAttacked = 1;
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::S)
                {
                    save();
                }
                else if (event.key.code == sf::Keyboard::L)
                {
                    load();
                }
            }
        }
        
        // Clear screen
        window.clear();
        
        // Render scene
        if(global::greenAmount == 0)
        {
            renderWinner(window, global::ORANGE);
        }
        else if(global::orangeAmount == 0)
        {
            renderWinner(window, global::GREEN);
        }
        else
        {
            render(window);
        }
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
    
    if(m_turn == global::ORANGE)
        playerTurn.setFillColor(sf::Color(255,128,0));
    else
        playerTurn.setFillColor(sf::Color(0, 200, 0));
    
    window.draw(playerTurn);
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
            {
                if(map[i][j]->getHP() <= 0)
                {
                    if(map[i][j]->getOwner() == global::ORANGE)
                        global::orangeAmount--;
                    else
                        global::greenAmount--;

                    delete map[i][j];
                    map[i][j] = nullptr;
                }
                else
                {
                    map[i][j]->draw(i, j, army, window);
                }
            }
        }
    }
}

void Game::renderWinner(sf::RenderWindow &window, bool winner)
{
    sf::Font font;
    font.loadFromFile(resourcePath() + "sansation.ttf");
    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(32);
    winnerText.setFillColor(sf::Color(255,255,255));
    
    if(winner == global::ORANGE)
        winnerText.setString("ORANGE wins");
    else
        winnerText.setString("GREEN wins");
    
    sf::FloatRect textRect = winnerText.getLocalBounds();
    winnerText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    winnerText.setPosition(global::W_WIDTH / 2.0f, global::W_HEIGHT / 2.0f);
    
    window.draw(winnerText);
}

void Game::save()
{
    nlohmann::json output;
    output["size"] = global::size;
    output["turn"] = m_turn;
    output["hasAttacked"] = m_hasAttacked;
    output["hasMoved"] = m_hasMoved;
    
    int k = 0;
    
    for(int i = 0; i < global::size; i++)
    {
        for (int j = 0; j < global::size; j++)
        {
            if(map[i][j] != nullptr)
            {
                map[i][j]->toJson(output, k);
            }
            else
            {
                output[std::to_string(k)]["type"] = "null";
            }
            k++;
        }
    }
    
    std::fstream file("save.json", std::fstream::out | std::fstream::trunc);
    if(!file.is_open())
        throw 1;
    file << std::setw(4) << output;
    file.close();
}

void Game::load()
{
    std::fstream inStream("save.json", std::fstream::in);
    nlohmann::json input;
    inStream >> input;
    inStream.close();
    
    for(int i = 0; i < global::size; i++)
    {
        for(int j = 0; j < global::size; j++)
        {
            if(map[i][j] != nullptr)
            {
                delete map[i][j];
                map[i][j] = nullptr;
            }
        }
    }
    
    global::orangeAmount = 0;
    global::greenAmount = 0;
    global::size = input["size"];
    m_turn = input["turn"];
    m_hasAttacked = input["hasAttacked"];
    m_hasMoved = input["hasMoved"];
    
    int k = 0;
    
    for(int i = 0; i < global::size; i++)
    {
        for(int j = 0; j < global::size; j++)
        {
            if(input[std::to_string(k)]["type"] == "null")
            {
                map[i][j] = nullptr;
            }
            else if (input[std::to_string(k)]["type"] == "archer") {
                map[i][j] = new ArcherEntity(
                                             input[std::to_string(k)]["hp"],
                                             input[std::to_string(k)]["orgHp"],
                                             input[std::to_string(k)]["attack"],
                                             input[std::to_string(k)]["orgAttack"],
                                             input[std::to_string(k)]["owner"],
                                             input[std::to_string(k)]["distance"]
                                             );
            }
            else if (input[std::to_string(k)]["type"] == "warrior") {
                map[i][j] = new WarriorEntity(
                                              input[std::to_string(k)]["hp"],
                                              input[std::to_string(k)]["orgHp"],
                                              input[std::to_string(k)]["attack"],
                                              input[std::to_string(k)]["orgAttack"],
                                              input[std::to_string(k)]["owner"]
                                              );
            }
            else if (input[std::to_string(k)]["type"] == "knight") {
                map[i][j] = new KnightEntity(
                                             input[std::to_string(k)]["hp"],
                                             input[std::to_string(k)]["orgHp"],
                                             input[std::to_string(k)]["attack"],
                                             input[std::to_string(k)]["orgAttack"],
                                             input[std::to_string(k)]["owner"]
                                             );
            }
            else if (input[std::to_string(k)]["type"] == "mage") {
                map[i][j] = new MageEntity(
                                           input[std::to_string(k)]["hp"],
                                           input[std::to_string(k)]["orgHp"],
                                           input[std::to_string(k)]["attack"],
                                           input[std::to_string(k)]["orgAttack"],
                                           input[std::to_string(k)]["owner"],
                                           input[std::to_string(k)]["distance"]
                                           );
            }
            else if (input[std::to_string(k)]["type"] == "cavalier") {
                map[i][j] = new CavalierEntity(
                                               input[std::to_string(k)]["hp"],
                                               input[std::to_string(k)]["orgHp"],
                                               input[std::to_string(k)]["attack"],
                                               input[std::to_string(k)]["orgAttack"],
                                               input[std::to_string(k)]["owner"]
                                               );
            }
            else
            {
                throw 3;
            }
            k++;
        }
    }
    
    inStream.close();
}
