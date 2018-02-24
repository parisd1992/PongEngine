//
//  FollowEntityAIComponent.hpp
//  PongGL
//
//  Created by David Paris on 12/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef FollowEntityAIComponent_hpp
#define FollowEntityAIComponent_hpp

#include <stdio.h>
#include "AIComponent.hpp"

/** Follows a given entity on the y axis **/
class FollowEntityAIComponent : public AIComponent
{
private:
    Entity* entityToFollow_;
public:
    FollowEntityAIComponent(Entity* entityToFollow) : entityToFollow_(entityToFollow)
    {}
    
    virtual ~FollowEntityAIComponent() {}
    virtual void update(Entity& entity);
};



#endif /* FollowEntityAIComponent_hpp */
