//
//  main.cpp
//  PongGL
//
//  An implementation of Pong using a physics and OpenGL rendering engine written from scratch in C++.
//
//  Physics Engine features:
//  - see World.hpp
//
//  OpenGL Rendering Engine features:
//  - see Graphics.hpp
//
//  Created by David Paris on 31/01/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "OpenGLView.hpp"
#include "Game.hpp"

/**
 This game is still in development.  The below provides a demo of the physics and graphics engine.
 5 balls with different wieghts and velocities bounce around a frame of boundary walls.
 **/
int main(int argc, const char * argv[]) {
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;
    
    //Load the view
    OpenGLView view {"PongEngine", WINDOW_WIDTH, WINDOW_HEIGHT};
    view.loadView();
    
    //unload the view
    view.unloadView();
    return 0;
}
