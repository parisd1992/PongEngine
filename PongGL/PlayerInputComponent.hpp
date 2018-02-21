//
//  PlayerInputComponent.hpp
//  PongGL
//
//  Created by David Paris on 11/02/2018.
//  Copyright © 2018 David Paris. All rights reserved.
//

#ifndef PlayerInputComponent_hpp
#define PlayerInputComponent_hpp

#include <stdio.h>
#include <queue>
#include "InputComponent.hpp"


/**
Class handles the player input by reading it from a queue
 **/
class PlayerInputComponent : public InputComponent
{
public:
    enum class Input
    {
        UP = 0,
        DOWN
    };
    
private:
    std::queue<Input> inputQueue_;

public:
    PlayerInputComponent(){}
    ~PlayerInputComponent(){}
    
    virtual void addInput(Input input);
    virtual void update(Entity& entity);
};

#endif /* PlayerInputComponent_hpp */
