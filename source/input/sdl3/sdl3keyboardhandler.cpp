#include "sdl3keyboardhandler.hpp"
#include "../inputmanager.hpp"

void SDL3KeyboardHandler::handleEvent(const SDL_Event& event, InputManager& manager)
{
    switch (event.type)
    {
        case SDL_EVENT_KEY_DOWN:
        {
            if (event.key.repeat) break;

            manager.setInput({INPUT_TYPE::KEYBOARD, static_cast<int>(event.key.scancode), 0}, true);
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            manager.setInput({INPUT_TYPE::KEYBOARD, static_cast<int>(event.key.scancode), 0}, false);
            break;
        }

        case SDL_EVENT_WINDOW_FOCUS_LOST:
        {
            manager.releaseAll(INPUT_TYPE::KEYBOARD);
            break;
        }
    }
}
