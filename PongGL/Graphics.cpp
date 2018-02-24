//
//  Graphics.cpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "Graphics.hpp"
#include "Entity.hpp"

/**
 Adds an Entity to be drawn in the current frame
 **/
void Graphics::addToFrame(Entity* entity)
{
    //points
    float left = (entity->getWidth() * -1.0f)/2;
    float right = (entity->getWidth())/2;
    float top = (entity->getHeight())/2;
    float bottom = (entity->getHeight() * -1.0f)/2;
    
    //verticies
    Vertice topLeft = { left, top };
    Vertice topRight = { right, top };
    Vertice bottomLeft = { left, bottom };
    Vertice bottomRight = { right, bottom };
    
    Colour colour = { 1.0f, 0.0f, 1.0f, 1.0f }; //TODO: entities should set their own colour
    Position position = { entity->getX(), entity->getY() };
    
    Drawable drawable;
    
    //add verticies
    drawable.verticies_.emplace_back(topLeft);
    drawable.verticies_.emplace_back(topRight);
    drawable.verticies_.emplace_back(bottomLeft);
    drawable.verticies_.emplace_back(bottomRight);
    
    //add vertice indexes
    drawable.verticeIndexes_.emplace_back(0);
    drawable.verticeIndexes_.emplace_back(1);
    drawable.verticeIndexes_.emplace_back(2);
    drawable.verticeIndexes_.emplace_back(2);
    drawable.verticeIndexes_.emplace_back(3);
    drawable.verticeIndexes_.emplace_back(1);
    
    //add colour
    drawable.colour_ = colour;
    
    //add position
    drawable.position_ = position;
    
    //TODO: Opportunity to use an object pool here if need be.
    frame_.emplace_back(drawable);
}

/**
 Returns the current frame
 **/
std::vector<Drawable> Graphics::getCurrentFrame()
{
    return frame_;
}

/**
 Removes all entities from the current frame
 **/
void Graphics::clearCurrentFrame()
{
    frame_.clear();
}
