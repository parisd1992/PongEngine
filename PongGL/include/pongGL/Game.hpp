//
//  Game.hpp
//  PongGL
//
//  Created by David Paris on 11/03/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

/*
 This class is responsible for the game logic, and progressing it during each frame.
 
 The below provides a demo of the physics and graphics engine.
 5 balls with different wieghts and velocities bounce around a frame of boundary walls.
 */

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>

#include "FreePhysicsComponent.hpp"
#include "JustDrawGraphicsComponent.hpp"
#include "World.hpp"
#include "Entity.hpp"

class Game
{
public:
    Game();
    ~Game();
    
    //setup the game
    void setup();
    
    //advances the game by 1 frame
    void advanceGame(GraphicsPipe* graphicsPipe);
    
    //send a message to the game
    void onMessage(int message);
    
    //tear down the game
    void tearDown();
    
private:
    World world;
    FreePhysicsComponent freePhysics;
    JustDrawGraphicsComponent justDrawGraphics;
    
    GraphicsPipe* graphicsPipe;
    std::vector<Entity*> gameEntities;

    void setupEntities();
};

#endif /* Game_hpp */
