#pragma once

#include <SDL3/SDL.h>

class InputManager;

class SDL3KeyboardHandler
{
    public:
        void handleEvent(const SDL_Event& event, InputManager& manager);
};