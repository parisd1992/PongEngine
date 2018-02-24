//
//  PhysicsComponent.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include <stdio.h>

class Entity;
class World;

/**
 Responsble for updating an entity based on physics
 **/
class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() {}
    virtual void update(Entity& o, World& world) = 0;
};

#endif /* PhysicsComponent_hpp */
