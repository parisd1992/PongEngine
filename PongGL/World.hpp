    //
//  World.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <vector>
#include "Entity.hpp"


/**
 Holds information on a colission.
 If isCollision and !isLeftRightCollision then is Top / Bottom collision
 **/
struct Collision
{
    bool isCollision = false;
    bool isLeftRightCollision = false;
};

/**
 The World class is responsible for creating a 'world' environment.
 It provides physics to any Entity that belongs to it.
 **/
class World
{
private:
    static const unsigned int MAX_SPEED = 100;
    
    /*
     Controls the speed we want to move for each iteration of continuos collision detection.
     Changing this could reduce / increase the accuracy at the cost of more compute per frame
     */
    static const unsigned int CONTINUOUS_COLLISION_ITERATION_SPEED = 5;
private:
    std::vector<Entity*> physicsEntities_;
    Collision collisionData_;
    
    /**
     Moves an entity according to its velocity and trajectory by a time step.
     Assumes timeStep is >=0 && <=1, else will set to the closer of 0 or 1
     **/
    void moveEntity(Entity& entity, float timeStep);
    
    /** Updates the collisionData_ between entity1 and entity2 **/
    void updateCollisionData(Entity& entity1, Entity& entity2);
    
    /** Updates the entity trajectory based on collision data **/
    void updateTrajectory(Entity& entity, Collision& collisionData);
    
    /** Updates the entity velocity based on the entity it's hit **/
    void updateVelocity(Entity& entity, Entity& hitEntity);
    
public:
    World() {}
    ~World() {}
    
    /** Adds an entity to the world **/
    void addEntity(Entity* entity);
    
    /**
     Handles any collisions in the world for an entity and provides and option for a callback.
     Uses a trivial implementation of continuous collision detection, which works best for objects with a width/height of at least 10
     **/
    template<class Callback>
    void handleCollision(Entity* entity, Callback callback)
    {
        //We take an iteratative approach to check for continuous collision
        unsigned int currentSpeed = abs(entity->getVelocity());
        unsigned int continousIterations = currentSpeed / CONTINUOUS_COLLISION_ITERATION_SPEED;
        unsigned int speedRemaining = currentSpeed % CONTINUOUS_COLLISION_ITERATION_SPEED;
        
        //if currentSpeed divides CONTINUOUS_COLLISION_ITERATION_SPEED exactly
        //we don't want to run an iteration for 0 remaining speed
        if (continousIterations > 0 && speedRemaining == 0)
        {
            --continousIterations;
        }
        //calculate time step
        float timeStep = continousIterations == 0 ? 1.0f : (float) CONTINUOUS_COLLISION_ITERATION_SPEED / (float) currentSpeed;
        
        unsigned int currentIteration = 0;
        while(currentIteration <= continousIterations)
        {
            //START CONTINUOUS COLLISION ITERATION
            moveEntity(*entity, timeStep);
            
            //check for collisions
            for(auto it = physicsEntities_.begin(); it != physicsEntities_.end(); ++it)
            {
                if(entity != *it)
                {
                    auto& hitEntity = *it;
                    updateCollisionData(*entity, *hitEntity);
                    
                    if (!collisionData_.isCollision)
                    {
                        continue;
                    }
                    else
                    {
                        //if the entity isn't moving - do nothing
                        if (!entity->getVelocity())
                        {
                            continue;
                        }
                        
                        updateTrajectory(*entity, collisionData_);
                        updateVelocity(*entity, *hitEntity);

                        //call the callback function
                        callback();
                    }
                }
            }
            
            ++currentIteration;
            //END CONTINUOUS COLLISION ITERATION
        }
    }
};

#endif /* World_hpp */
