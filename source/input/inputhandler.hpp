#pragma once

#include "inputmanager.hpp"

class InputHandler
{
    public:
        virtual ~InputHandler() = default;
        virtual void update(InputManager& manager) = 0;
};