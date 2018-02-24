//
//  World.cpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "World.hpp"

void World::addEntity(Entity *entity)
{
    physicsEntities_.emplace_back(entity);
}

void World::moveEntity(Entity &entity, float timeStep)
{
    if (timeStep > 1.0f)
    {
        timeStep = 1.0f;
    }
    
    if (timeStep < 0.0f)
    {
        timeStep = 0.0f;
    }
    
    entity.setX((float) entity.getX() + entity.getVelocity() * timeStep * cosf(entity.getTrajectory()));
    entity.setY((float) entity.getY() + entity.getVelocity() * timeStep * sinf(entity.getTrajectory()));
}

void World::updateCollisionData(Entity &entity1, Entity &entity2)
{
    //check the if the bounding boxes intersect:
    //min is top left, max is bottom right
    int e1MinX = entity1.getX() - entity1.getWidth() / 2;
    int e1MinY = entity1.getY() + entity1.getHeight() / 2;
    
    int e1MaxX = entity1.getX() + entity1.getWidth() / 2;
    int e1MaxY = entity1.getY() - entity1.getHeight() / 2;
    
    int e2MinX = entity2.getX() - entity2.getWidth() / 2;
    int e2MinY = entity2.getY() + entity2.getHeight() / 2;
    
    int e2MaxX = entity2.getX() + entity2.getWidth() / 2;
    int e2MaxY = entity2.getY() - entity2.getHeight() / 2;
    
    if ((e1MaxX < e2MinX || e1MinX > e2MaxX) || (e1MaxY > e2MinY || e1MinY < e2MaxY))
    {
        collisionData_.isCollision = false;
    }
    else
    {
        collisionData_.isCollision = true;
        //Where was the collision?  Top/bottom lines or left/right?
        if ((e1MinX < e2MinX && e1MaxX >= e2MinX) || (e1MinX <= e2MaxX && e1MaxX > e2MaxX)) //left/right?
        {
            collisionData_.isLeftRightCollision = true;
        }
        else
        {
            collisionData_.isLeftRightCollision = false;
        }
    }
}

void World::updateTrajectory(Entity &entity, Collision &collisionData)
{
    //update the trajectory:
    //- 0 trajectory becomes 180 degrees
    //- 180 trajetory becomes 0
    //- angle of incidence = angle of reflection in opposite direction
    if (0 == entity.getTrajectory())
    {
        entity.setTrajectory(Math::PI);
    }
    else if (Math::PI == entity.getTrajectory())
    {
        entity.setTrajectory(0);
    }
    else
    {
        //Where was the collision?
        if (collisionData.isLeftRightCollision)
        {
            entity.setTrajectory((2*Math::PI - entity.getTrajectory())+(Math::PI));
        }
        else //top/bottom
        {
            entity.setTrajectory(2*Math::PI - entity.getTrajectory());
        }
    }
}

void World::updateVelocity(Entity &entity, Entity &hitEntity)
{
    //update the velocity
    //0 weight = infinite weight
    //if 2 entities of infinite weight hit, velocity becomes 0
    if (entity.getWeight() == 0 && hitEntity.getWeight() == 0)
    {
        entity.setVelocity(0);
    }
    else
    {
        //if entity is lighter than what it's hit:
        //velocity = velocity(entity) + 1
        if (entity.getWeight() != 0 && (entity.getWeight() < hitEntity.getWeight() || hitEntity.getWeight() == 0))
        {
            //only update the velocity if it is less than MAX_SPEED
            if (abs(entity.getVelocity()) < MAX_SPEED)
            {
                if (entity.getVelocity() < 0) //we want to keep the direction of the velocity (+ / -)
                {
                    entity.setVelocity(entity.getVelocity()-1);
                }
                else
                {
                    entity.setVelocity(entity.getVelocity()+1);
                }
            }
        }
        //so if entities are the same weight, their velocities do not change
    }
}
