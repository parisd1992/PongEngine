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
class Graphics;

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(Entity& o, Graphics& graphics) = 0;
};

#endif /* GraphicsComponent_hpp */
