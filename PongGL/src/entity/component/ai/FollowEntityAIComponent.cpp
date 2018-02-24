//
//  FollowEntityAIComponent.cpp
//  PongGL
//
//  Created by David Paris on 12/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "FollowEntityAIComponent.hpp"
#include "Entity.hpp"

void FollowEntityAIComponent::update(Entity &entity)
{
    if (entityToFollow_->getY() > entity.getY())
    {
        entity.setVelocity(entity.getVelocity()+2);
    }
    else if (entityToFollow_->getY() < entity.getY())
    {
        entity.setVelocity(entity.getVelocity()-2);
    }
    else
    {
        //if equal do nothing
    }
}
