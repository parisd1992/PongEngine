//
//  GoalPhysicsComponent.cpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "GoalPhysicsComponent.hpp"
#include "World.hpp"

void GoalPhysicsComponent::update(Entity &entity, World &world)
{
    world.handleCollision(&entity, [this]() {score_ += 1;});
}
