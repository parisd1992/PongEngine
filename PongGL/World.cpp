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
