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
    glfwInit();

    /***************
     * Set up GLFW
     ***************/

    //OpenGL 3.2 +
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //Only support new core functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //make window resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Create the window and add to context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    /***************
     * Set up Characters
     ***************/
    
    //renderer
    RenderQueue queue{800, 600};
    Renderer renderer(&queue);
    renderer.init();
    
    //ball and paddles
    PhysicsComponent* freePhysics = new FreePhysicsComponent();
    
    //ball 1
    Sprite ballSprite{10, 10, 1.0f, 1.0f, 0.0f};
    GraphicsComponent* justDrawBall = new JustDrawGraphicsComponent(&ballSprite);
    Entity* ball1 = new Entity(0, -250.0f, 0.0f, 10, 10, 5, Math::PI/3, 5, nullptr, freePhysics, nullptr, justDrawBall);
    Entity* ball2 = new Entity(0, 250.0f, 0.0f, 10, 10, -5, Math::PI/3, 5, nullptr, freePhysics, nullptr, justDrawBall);
    Entity* ball3 = new Entity(0, 50.0f, 0.0f, 10, 10, 5, Math::PI/3, 5, nullptr, freePhysics, nullptr, justDrawBall);
    Entity* ball4 = new Entity(0, 200.0f, 0.0f, 10, 10, -5, Math::PI/3, 5, nullptr, freePhysics, nullptr, justDrawBall);
    Entity* ball5 = new Entity(0, 100.0f, 0.0f, 10, 10, 5, Math::PI/3, 5, nullptr, freePhysics, nullptr, justDrawBall);
    
    //top and bottom wall
    Sprite wallSprite{800, 15, 1.0f, 1.0f, 0.0f};
    GraphicsComponent* justDrawWall = new JustDrawGraphicsComponent(&wallSprite);
    Entity* topWall = new Entity(1, 0, 300.0f, 800.0f, 30, 0, 0, 0, nullptr, freePhysics, nullptr, justDrawWall);
    Entity* bottomWall = new Entity(2, 0, -300.0f, 800.0f, 30, 0, 0, 0, nullptr, freePhysics, nullptr, justDrawWall);
    
    //left and right  wall
    Sprite sideSprite{15, 600, 1.0f, 1.0f, 0.0f};
    GraphicsComponent* justDrawSide = new JustDrawGraphicsComponent(&sideSprite);
    Entity* leftWall = new Entity(3, -400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, freePhysics, nullptr, justDrawSide);
    Entity* rightWall = new Entity(4, 400.0f, 0.0f, 30, 600, 0, 0, 0, nullptr, freePhysics, nullptr, justDrawSide);
    
    //world and graphics
    World* world = new World();
    Graphics* graphics = new Graphics(&queue);
    
    //add to physics
    world->addEntity(ball1);
    world->addEntity(ball2);
    world->addEntity(ball3);
    world->addEntity(ball4);
    world->addEntity(ball5);
    world->addEntity(topWall);
    world->addEntity(bottomWall);
    world->addEntity(leftWall);
    world->addEntity(rightWall);
    
    double MS_PER_FRAME = 1000/60;
    
    while(!glfwWindowShouldClose(window))
    {
        auto t_start = std::chrono::system_clock::now();
        
        ball1->update(*world, *graphics);
        ball2->update(*world, *graphics);
        ball3->update(*world, *graphics);
        ball4->update(*world, *graphics);
        ball5->update(*world, *graphics);
        topWall->update(*world, *graphics);
        bottomWall->update(*world, *graphics);
        leftWall->update(*world, *graphics);
        rightWall->update(*world, *graphics);
        
        renderer.render();
        
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
    
    delete freePhysics;
    delete justDrawBall;
    delete justDrawSide;
    delete justDrawWall;
    delete ball1;
    delete ball2;
    delete ball3;
    delete ball4;
    delete ball5;
    delete topWall;
    delete bottomWall;
    delete leftWall;
    delete rightWall;
    delete world;
    delete graphics;
    
    glfwTerminate();
    return 0;
}
