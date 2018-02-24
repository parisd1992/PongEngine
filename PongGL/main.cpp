//
//  main.cpp
//  PongGL
//
//  Created by David Paris on 31/01/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "Renderer.hpp"
#include "FreePhysicsComponent.hpp"
#include "JustDrawGraphicsComponent.hpp"
#include "World.hpp"
#include "Graphics.hpp"
#include "Entity.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;
    
    /***************
     * Set up GLFW
     ***************/
    glfwInit();
    //OpenGL 3.2 +
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //Only support new core functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //make window resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Create the window and add to context
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "PongEngine", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    /***************
     * Set up Graphics Engine
     ***************/
    Graphics graphics;
    Renderer openGLRenderer {&graphics, static_cast<float>(windowWidth), static_cast<float>(windowHeight)};
    openGLRenderer.init();
    
    /***************
     * Set up Physics Engine
     ***************/
    World world;
    
    /***************
     * Set up Components
     ***************/
    FreePhysicsComponent freePhysics;
    JustDrawGraphicsComponent justDrawGraphics;
    
    /***************
     * Set up Enitities
     ***************/
    std::vector<Entity*> gameEntities;
    
    Entity ball1 {0, -250.0f, 0.0f, 10, 10, 5, Math::PI/7, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&ball1);
    gameEntities.emplace_back(&ball1);
    
    Entity ball2 {1, 250.0f, 0.0f, 10, 10, -5, 2*Math::PI/9, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&ball2);
    gameEntities.emplace_back(&ball2);
    
    Entity ball3 {2, 50.0f, 0.0f, 10, 10, 5, Math::PI/4, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&ball3);
    gameEntities.emplace_back(&ball3);
    
    Entity ball4 {3, 200.0f, 0.0f, 10, 10, -5, 2*Math::PI/3, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&ball4);
    gameEntities.emplace_back(&ball4);
    
    Entity ball5 {4, 100.0f, 0.0f, 10, 10, 5, Math::PI/6, 5, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&ball5);
    gameEntities.emplace_back(&ball5);
    
    Entity topWall {5, 0.0f, 300.0f, 800, 30, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&topWall);
    gameEntities.emplace_back(&topWall);
    
    Entity bottomWall {6, 0.0f, -300.0f, 800, 30, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&bottomWall);
    gameEntities.emplace_back(&bottomWall);
    
    //left and right  wall
    Entity leftWall {7, -400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&leftWall);
    gameEntities.emplace_back(&leftWall);
    
    Entity rightWall {8, 400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, &freePhysics, nullptr, &justDrawGraphics};
    world.addEntity(&rightWall);
    gameEntities.emplace_back(&rightWall);
    
    
    double MS_PER_FRAME = 1000/60;
    
    while(!glfwWindowShouldClose(window))
    {
        auto t_start = std::chrono::system_clock::now();
        
        for(auto iter = gameEntities.begin(); iter != gameEntities.end(); ++iter)
        {
            (*iter)->update(world, graphics);
        }
        
        openGLRenderer.render();
        
        glfwSwapBuffers(window); //double buffering
        glfwPollEvents(); //window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        
        auto t_end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_end-t_start;
        
        std::cout << "elapsed time: " << elapsed_seconds.count()*1000 << "ms\n";
        std::cout << "sleep time: " << (MS_PER_FRAME - elapsed_seconds.count()*1000) / 1000 << "s\n";
        
        std::this_thread::sleep_for(std::chrono::duration<double>((MS_PER_FRAME - elapsed_seconds.count()*1000)/1000));
    }
    
    glfwTerminate();
    return 0;
}
