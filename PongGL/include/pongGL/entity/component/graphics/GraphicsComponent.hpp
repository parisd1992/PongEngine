//
//  GraphicsComponent.hpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include <stdio.h>

class Entity;
class GraphicsPipe;

/**
 Responsble for updating an entity based on graphics
 **/
class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(Entity& o, GraphicsPipe& graphics) = 0;
};

#endif /* GraphicsComponent_hpp */
