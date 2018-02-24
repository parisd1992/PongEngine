//
//  FreePhysicsComponent.hpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef FreePhysicsComponent_hpp
#define FreePhysicsComponent_hpp

#include <stdio.h>
#include "PhysicsComponent.hpp"

/**
 Default PhysicsComponent that delegates to the world physics
 **/
class FreePhysicsComponent : public PhysicsComponent
{
public:
    FreePhysicsComponent() {}
    
    virtual ~FreePhysicsComponent() {}
    virtual void update(Entity& entity, World& world);
    
};

#endif /* FreePhysicsComponent_hpp */
