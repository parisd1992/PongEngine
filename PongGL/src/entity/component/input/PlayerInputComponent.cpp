//
//  PlayerInputComponent.cpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#include "PlayerInputComponent.hpp"
#include "Entity.hpp"

void PlayerInputComponent::addInput(PlayerInputComponent::Input input)
{
    inputQueue_.push(input);
}

void PlayerInputComponent::update(Entity &entity)
{
    if(!inputQueue_.empty())
    {
        Input input = inputQueue_.front();
        
        switch (input) {
            case Input::UP:
                entity.setVelocity(entity.getVelocity()+5);
                break;
            case Input::DOWN:
                entity.setVelocity(entity.getVelocity()-5);
                break;
            default:
                break;
        }
        
        inputQueue_.pop();
    }
}
