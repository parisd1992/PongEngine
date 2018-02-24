//
//  Entity.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <cmath>
#include "Math.hpp"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;
class AIComponent;
class World;
class Graphics;

/**
 An Entity is a game object with behaviour that is driven by its components.
 Its x and y fields represent the position of the centre of the Entity.
 **/
class Entity
{
private:
    int id_;
    InputComponent* input_;
    PhysicsComponent* physics_;
    AIComponent* ai_;
    GraphicsComponent* graphics_;
    
    float x_, y_;
    unsigned int width_, height_;
    int velocity_;
    double trajectory_;
    unsigned int weight_;
    
public:
    Entity(int id, float x, float y, unsigned int width, unsigned int height, int velocity, double trajectory, unsigned int weight,
           InputComponent* input, PhysicsComponent* physics, AIComponent* ai, GraphicsComponent* graphics)
    : id_(id),
    x_(x),
    y_(y),
    width_(width),
    height_(height),
    velocity_(velocity),
    weight_(weight),
    input_(input),
    physics_(physics),
    ai_(ai),
    graphics_(graphics)
    {
        setTrajectory(trajectory);
    }
    
    ~Entity()
    {}
    
    /** Updates the entity's state **/
    void update(World& world, Graphics& graphics);
    
    int getId()
    {
        return id_;
    }
    
    void setX(float x)
    {
        x_ = x;
    }
    
    float getX()
    {
        return x_;
    }
    
    void setY(float y)
    {
        y_ = y;
    }
    
    float getY()
    {
        return y_;
    }
    
    unsigned int getWidth()
    {
        return width_;
    }
    
    unsigned int getHeight()
    {
        return height_;
    }
    
    void setVelocity(int velocity)
    {
        velocity_ = velocity;
    }
    
    int getVelocity()
    {
        return velocity_;
    }
    
    double getTrajectory()
    {
        return trajectory_;
    }
    
    /** Set the trajectory, making sure it remains within 360 degrees (2PI) **/
    void setTrajectory(double trajectory)
    {
        if (trajectory >= 0)
        {
            trajectory_ = std::fmod(trajectory, (Math::PI * 2));
        }
    }
    
    unsigned int getWeight()
    {
        return weight_;
    }
};

#endif /* Entity_hpp */
