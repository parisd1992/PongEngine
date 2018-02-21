//
//  GoalPhysicsComponent.hpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef GoalPhysicsComponent_hpp
#define GoalPhysicsComponent_hpp

#include <stdio.h>
#include "PhysicsComponent.hpp"

/**
 GoalPhysicsComponent updates a score everytime there is a collision
 **/
class GoalPhysicsComponent : PhysicsComponent
{
private:
    unsigned int score_;
    
public:
    GoalPhysicsComponent(unsigned int score) : score_(score) {}
    virtual ~GoalPhysicsComponent() {}
    virtual void update(Entity& entity, World& world);
    
    void setScore(unsigned int score)
    {
        score_ = score;
    }
    
    unsigned int getScore()
    {
        return score_;
    }
};

#endif /* GoalPhysicsComponent_hpp */
