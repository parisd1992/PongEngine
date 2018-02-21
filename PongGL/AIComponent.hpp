//
//  AIComponent.hpp
//  PongGL
//
//  Created by David Paris on 12/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef AIComponent_hpp
#define AIComponent_hpp

#include <stdio.h>

class Entity;

class AIComponent
{
public:
    virtual ~AIComponent() {}
    virtual void update(Entity& o) = 0;
};

#endif /* AIComponent_hpp */
