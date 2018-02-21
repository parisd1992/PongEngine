//
//  Graphics.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef Graphics_hpp
#define Graphics_hpp

#include <stdio.h>
#include "Sprite.hpp"
#include "Renderer.hpp"

class Entity;

/**
 Graphics class handles rendering
 **/
class Graphics
{
private:
    RenderQueue* renderQueue_;
    
public:
    Graphics(RenderQueue* renderQueue_) : renderQueue_(renderQueue_) {}
    ~Graphics(){}
    
    /**
     Draw a sprite to the graphics context
     **/
    void draw(Sprite* sprite, float x, float y);
    
};

#endif /* Graphics_hpp */


