#include <SDL3/SDL.h>
#include "sdl3input.hpp"

SDL3KeyboardHandler keyboardHandler;
SDL3ControllerHandler controllerHandler;
SDL3TouchHandler touchHandler;

void initInput()
{
    inputManager.init();
    controllerHandler.init(inputManager);

    inputManager.bind(FUNKIN_ACTION::NOTE_LEFT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_LEFT});
    inputManager.bind(FUNKIN_ACTION::NOTE_DOWN, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_DOWN});
    inputManager.bind(FUNKIN_ACTION::NOTE_UP, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_UP});
    inputManager.bind(FUNKIN_ACTION::NOTE_RIGHT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_RIGHT});
    inputManager.bind(FUNKIN_ACTION::ACCEPT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_RETURN});
    inputManager.bind(FUNKIN_ACTION::BACK, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_ESCAPE});
}