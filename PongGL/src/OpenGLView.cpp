//
//  OpenGLView.cpp
//  PongGL
//
//  Created by David Paris on 11/03/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "OpenGLView.hpp"
#include <iostream>
#include <chrono>
#include <thread>

OpenGLView::OpenGLView(std::string name, unsigned int width, unsigned int height)
: windowName_(name), windowWidth_(width), windowHeight_(height)
{}

unsigned int OpenGLView::getWindowWidth() const { return windowWidth_; }
unsigned int OpenGLView::getWindowHeight() const { return windowHeight_; }

void OpenGLView::loadView()
{
    setupGLFW();
    
    openGLRenderer_.init(&graphicsPipe_, static_cast<float>(getWindowWidth()), static_cast<float>(getWindowHeight()));
    game_.setup();
    
    constexpr double MS_PER_FRAME = 1000/60; //60 FPS
    
    while(!glfwWindowShouldClose(window_))
    {
        auto t_start = std::chrono::system_clock::now();
        
        game_.advanceGame(&graphicsPipe_);
        
        openGLRenderer_.render();
        
        glfwSwapBuffers(window_); //double buffering
        glfwPollEvents(); //window events
        
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window_, GL_TRUE);
        }
        
        auto t_end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_end-t_start;
        sleepViewBetweenFrames(elapsed_seconds, MS_PER_FRAME);
    }
}

void OpenGLView::unloadView()
{
    game_.tearDown();
    glfwTerminate();
}

void OpenGLView::setupGLFW()
{
    glfwInit();
    //OpenGL 3.2 +
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //Only support new core functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //make window non resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Create the window and add to context
    window_ = glfwCreateWindow(getWindowWidth(), getWindowHeight(), windowName_.c_str(), nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window_);
}
                                        
void OpenGLView::sleepViewBetweenFrames(std::chrono::duration<double> secFrameDuration, double msPerFrame)
{
    auto elapsedMS = secFrameDuration.count()*1000;
    auto sleepS = (msPerFrame - elapsedMS) / 1000;
    
    std::cout << "elapsed time: " << elapsedMS << "ms" << std::endl;
    std::cout << "sleep time: " << sleepS << "s" << std::endl;
    
    if (sleepS > 0)
    {
        std::this_thread::sleep_for(std::chrono::duration<double>(sleepS));
    }
}
