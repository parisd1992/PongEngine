//
//  InputComponent.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include <stdio.h>

class Entity;

class InputComponent
{
public:
    virtual ~InputComponent() {}
    virtual void update(Entity& o) = 0;
};

#endif /* InputComponent_hpp */
