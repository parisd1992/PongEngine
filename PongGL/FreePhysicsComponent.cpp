//
//  FreePhysicsComponent.cpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "FreePhysicsComponent.hpp"
#include "World.hpp"

void FreePhysicsComponent::update(Entity &entity, World &world)
{
    world.handleCollision(&entity, []{});
}
