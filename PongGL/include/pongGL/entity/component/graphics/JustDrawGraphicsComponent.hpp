//
//  JustDrawGraphicsComponent.hpp
//  PongGL
//
//  Created by David Paris on 12/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef JustDrawGraphicsComponent_hpp
#define JustDrawGraphicsComponent_hpp

#include <stdio.h>
#include "GraphicsComponent.hpp"

class JustDrawGraphicsComponent : public GraphicsComponent
{
public:
    JustDrawGraphicsComponent(){}
    ~JustDrawGraphicsComponent() {}
    
    virtual void update(Entity& o, GraphicsPipe& graphics);
};

#endif /* JustDrawGraphicsComponent_hpp */
