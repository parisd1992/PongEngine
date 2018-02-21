//
//  JustDrawGraphicsComponent.cpp
//  PongGL
//
//  Created by David Paris on 12/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "JustDrawGraphicsComponent.hpp"
#include "Graphics.hpp"
#include "Entity.hpp"

void JustDrawGraphicsComponent::update(Entity &o, Graphics &graphics)
{
    graphics.draw(sprite_, o.getX(), o.getY());
}
