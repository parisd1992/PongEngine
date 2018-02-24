//
//  Entity.cpp
//  PongGL
//
//  Created by David Paris on 05/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "Entity.hpp"
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "AIComponent.hpp"
#include "GraphicsComponent.hpp"

void Entity::update(World &world, Graphics &graphics)
{
    if (input_) {input_->update(*this);}
    if (physics_) {physics_->update(*this, world);}
    if (ai_) {ai_->update(*this);}
    if (graphics_) {graphics_->update(*this, graphics);}
}
