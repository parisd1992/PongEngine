//
//  OpenGLView.hpp
//  PongGL
//
//  Created by David Paris on 11/03/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

/**
 This class acts as the view in a MVC pattern, and is responsible for all user interations.
 It loads the Game class and provides it a GraphicsPipe which can be used to render to the view.
 For game logic see the Game class.
 */

#ifndef OpenGLView_hpp
#define OpenGLView_hpp

#include <stdio.h>
#include <string>
#include <chrono>
#include "Renderer.hpp"
#include "Graphics.hpp"
#include "Game.hpp"
#include <GLFW/glfw3.h>

class OpenGLView
{
public:
    unsigned int getWindowWidth() const;
    unsigned int getWindowHeight() const;
    
    OpenGLView(std::string name, unsigned int width, unsigned int height);
    
    //loads the view to screen, kicking off the game loop
    void loadView();

    //unloads the view from screen
    void unloadView();
    

private:
    
    //window related fields
    unsigned int windowWidth_;
    unsigned int windowHeight_;
    std::string windowName_;
    GLFWwindow* window_;
    
    //graphics fields
    GraphicsPipe graphicsPipe_;
    Renderer openGLRenderer_;
    
    //game
    Game game_;
    
    void setupGLFW();

    /**
     Sleep to ensure framerate.
     TODO: If too slow don't sleep.  Remove sleep using fixed update time step, with variable rendering?
     See: http://gameprogrammingpatterns.com/game-loop.html
     **/
    void sleepViewBetweenFrames(std::chrono::duration<double> secFrameDuration, double msPerFrame);
    
};

#endif /* OpenGLView_hpp */
