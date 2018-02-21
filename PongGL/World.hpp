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

class World
{
private:
    std::vector<Entity*> gameEntities_;
    
public:
    World() {}
    ~World() {}
    
    /** Adds an entity to the world **/
    void addEntity(Entity* entity);
    
    /** handles any collisions in the world for an entity and provides and option for a callback  **/
    template<class Callback>
    void handleCollision(Entity* entity, Callback callback)
    {
        //move the entity
        if (entity->getType() == 0)
        {
            printf("t: %0.9f\n", entity->getTrajectory());
            printf("x: %0.9f\n", entity->getX());
        }
        
        entity->setX((float) entity->getX()+entity->getVelocity() * cosf(entity->getTrajectory()));
        entity->setY((float) entity->getY()+entity->getVelocity() * sinf(entity->getTrajectory()));
        
        //check for collisions
        for(auto it = gameEntities_.begin(); it != gameEntities_.end(); it++)
        {
            if(entity != *it)
            {
                auto& hitEntity = *it;
                //check the if the bounding boxes intersect:
                //min is top left, max is bottom right
                int e1MinX = entity->getX() - (entity)->getWidth() / 2;
                int e1MinY = entity->getY() + (entity)->getHeight() / 2;
                
                int e1MaxX = entity->getX() + (entity)->getWidth() / 2;
                int e1MaxY = entity->getY() - (entity)->getHeight() / 2;
                
                int e2MinX = hitEntity->getX() - hitEntity->getWidth() / 2;
                int e2MinY = hitEntity->getY() + hitEntity->getHeight() / 2;
                
                int e2MaxX = hitEntity->getX() + hitEntity->getWidth() / 2;
                int e2MaxY = hitEntity->getY() - hitEntity->getHeight() / 2;
                
                if ((e1MaxX < e2MinX || e1MinX > e2MaxX) || (e1MaxY > e2MinY || e1MinY < e2MaxY))
                {
                    continue; //no collision
                }
                else //collision
                {
                    //if the entity isn't moving - do nothing
                    if (!entity->getVelocity())
                    {
                        continue;
                    }
                    
                    //update the trajectory:
                    //- 0 trajectory becomes 180 degrees
                    //- 180 trajetory becomes 0
                    //- angle of incidence = angle of reflection in opposite direction
                    if (0 == entity->getTrajectory())
                    {
                        entity->setTrajectory(Math::PI);
                    }
                    else if (Math::PI == entity->getTrajectory())
                    {
                        entity->setTrajectory(0);
                    }
                    else
                    {
                        //where was the collision?  Top/bottom lines or left/right?
                        //Left/Right?
                        if (e1MinX < e2MinX && e1MaxX >= e2MinX) //right hit left so we rotate the normal by 270 deg
                        {
                            entity->setTrajectory((2*Math::PI - entity->getTrajectory())+(Math::PI));
                        }
                        else if (e1MinX <= e2MaxX && e1MaxX > e2MaxX) //left hit right so we rotate the normal by 180 deg
                        {
                            entity->setTrajectory((2*Math::PI - entity->getTrajectory())+(Math::PI));
                        }
                        else
                        {
                            entity->setTrajectory(2*Math::PI - entity->getTrajectory());
                        }
                    }
                    
                    //update the velocity
                    //0 weight = infinite weight
                    //if 2 entities of infinite weight hit, velocity becomes 0
                    if (entity->getWeight() == 0 && hitEntity->getWeight() == 0)
                    {
                        entity->setVelocity(0);
                    }
                    else
                    {
                        //if entity is lighter than what it's hit, velocity = v(entity) + v(hit)
                        if (entity->getWeight() != 0 && (entity->getWeight() < hitEntity->getWeight() || hitEntity->getWeight() == 0))
                        {
                            entity->setVelocity(entity->getVelocity()+hitEntity->getVelocity());
                        }
                        //so if entities are the same weight, their velocities do not change
                    }
                    
                    //call the callback function
                    callback();
                }
            }
        }
    }
};

#endif /* World_hpp */
