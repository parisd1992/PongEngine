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
#include <vector>

class Entity;

struct Position
{
    float x_;
    float y_;
};

/** A vertex that makes up a Drawable in object coordinates **/
struct Vertice
{
    float x_;
    float y_;
};

struct Colour
{
    float red_;
    float green_;
    float blue_;
    float alpha_;
};

/**
 Something we want to draw in the current frame.
 Vertices are in object coordinates
 **/
struct Drawable
{
    std::vector<Vertice> verticies_;
    std::vector<unsigned int> verticeIndexes_;
    Colour colour_;
    Position position_;
};

/**
 The Graphics class holds the things we want to draw in the current frame
 as a Drawable.  It acts like a pipe.
 **/
class Graphics
{
private:
    //TODO:
    //As we populate the frame, the renderer might try to render what's in it.
    //There is a risk the renderer will keep on rendering if we keep on updating the frame.
    //We should introduce a way for 'locking' down the frame, e.g. double buffering?
    std::vector<Drawable> frame_;
    
public:
    Graphics(){}
    ~Graphics(){}
    
    /**
     Adds an Entity to be drawn in the current frame
     **/
    void addToFrame(Entity* entity);
    
    /**
     Returns the current frame
     **/
    std::vector<Drawable> getCurrentFrame();
    
    /**
     Removes all entities from the current frame
     **/
    void clearCurrentFrame();
    
};

#endif /* Graphics_hpp */


