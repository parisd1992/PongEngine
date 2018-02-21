//
//  Graphics.cpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "Graphics.hpp"

void Graphics::draw(Sprite *sprite, float x, float y)
{
    renderQueue_->addToQueue(sprite, x, y);
}
