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
        //move the entity
        //We take an iteratative approach to check for continuous collision
        unsigned int currentSpeed = abs(entity->getVelocity());
        unsigned int continousIterations = currentSpeed / CONTINUOUS_COLLISION_ITERATION_SPEED;
        
        unsigned int currentIteration = 0;
        
        //START CONTINUOUS ITERATION
        while(currentIteration <= continousIterations)
        {
            float timeStep = continousIterations == 0 ? 1.0f : 1.0f / (float) continousIterations;
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
                    else //collision
                    {
                        //if the entity isn't moving - do nothing
                        if (!entity->getVelocity())
                        {
                            continue;
                        }
                        
                        updateTrajectory(*entity, collisionData_);
                        
                        //update the velocity
                        //0 weight = infinite weight
                        //if 2 entities of infinite weight hit, velocity becomes 0
                        if (entity->getWeight() == 0 && hitEntity->getWeight() == 0)
                        {
                            entity->setVelocity(0);
                        }
                        else
                        {
                            //if entity is lighter than what it's hit:
                            //velocity = velocity(entity) + 1
                            if (entity->getWeight() != 0 && (entity->getWeight() < hitEntity->getWeight() || hitEntity->getWeight() == 0))
                            {
                                //only update the velocity if it is less than MAX_SPEED
                                if (abs(entity->getVelocity()) < MAX_SPEED)
                                {
                                    if (entity->getVelocity() < 0) //we want to keep the direction of the velocity (+ / -)
                                    {
                                        entity->setVelocity(entity->getVelocity()-1);
                                    }
                                    else
                                    {
                                        entity->setVelocity(entity->getVelocity()+1);
                                    }
                                }
                            }
                            //so if entities are the same weight, their velocities do not change
                        }
                        
                        //call the callback function
                        callback();
                    }
                }
            }
            
            ++currentIteration;
            //END CONTINUOUS ITERATION
        }
    }
};

#endif /* World_hpp */
