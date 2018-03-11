//
//  Game.cpp
//  PongGL
//
//  Created by David Paris on 11/03/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::setup()
{
    setupEntities();
}

void Game::advanceGame(GraphicsPipe* graphicsPipe)
{
    for(auto gameEntity : gameEntities)
    {
        gameEntity->update(world, *graphicsPipe);
    }
}

void Game::onMessage(int message)
{
    //TODO
}

void Game::tearDown()
{
    for(auto gameEntity : gameEntities)
    {
        delete gameEntity;
    }
}

void Game::setupEntities()
{
    Entity* ball1 = new Entity(0, -250.0f, 0.0f, 10, 10, 1, Math::PI/7, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(ball1);
    gameEntities.emplace_back(ball1);
    
    Entity* ball2 = new Entity(1, 250.0f, 0.0f, 10, 10, -2, 2*Math::PI/9, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(ball2);
    gameEntities.emplace_back(ball2);
    
    Entity* ball3 = new Entity(2, 50.0f, 0.0f, 10, 10, 3, Math::PI/4, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(ball3);
    gameEntities.emplace_back(ball3);
    
    Entity* ball4 = new Entity(3, 200.0f, 0.0f, 10, 10, -4, 2*Math::PI/3, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(ball4);
    gameEntities.emplace_back(ball4);
    
    Entity* ball5 = new Entity(4, 100.0f, 0.0f, 10, 10, 5, Math::PI/6, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(ball5);
    gameEntities.emplace_back(ball5);
    
    Entity* topWall = new Entity(5, 0.0f, 300.0f, 800, 30, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(topWall);
    gameEntities.emplace_back(topWall);
    
    Entity* bottomWall = new Entity(6, 0.0f, -300.0f, 800, 30, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(bottomWall);
    gameEntities.emplace_back(bottomWall);
    
    //left and right  wall
    Entity* leftWall = new Entity(7, -400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(leftWall);
    gameEntities.emplace_back(leftWall);
    
    Entity* rightWall = new Entity(8, 400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics);
    world.addEntity(rightWall);
    gameEntities.emplace_back(rightWall);
}
