//
//  Sprite.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>

class Sprite
{
private:
    unsigned int width_;
    unsigned int height_;
    float red_;
    float blue_;
    float green_;
    
public:
    
    /**
     Create a sprite with a width, height (in pixels) and a fraction of red, blue and green (between 1.0f and 0.0f)
     **/
    Sprite(unsigned int width, unsigned int height, float red, float blue, float green)
        : width_(width), height_(height), red_(red), blue_(blue), green_(green)
    {
        
    }
    
    int getWidth()
    {
        return width_;
    }
    
    int getHeight()
    {
        return height_;
    }
    
    float getRed()
    {
        return red_;
    }
    
    float getBlue()
    {
        return blue_;
    }
    
    float getGreen()
    {
        return green_;
    }
    
    
    
    
};

#endif /* Sprite_hpp */
