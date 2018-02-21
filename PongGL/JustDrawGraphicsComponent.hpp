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
#include "Sprite.hpp"

class JustDrawGraphicsComponent : public GraphicsComponent
{
private:
    Sprite* sprite_;
public:
    JustDrawGraphicsComponent(Sprite* sprite) : sprite_(sprite) {}
    ~JustDrawGraphicsComponent() {}
    
    virtual void update(Entity& o, Graphics& graphics);
};

#endif /* JustDrawGraphicsComponent_hpp */
