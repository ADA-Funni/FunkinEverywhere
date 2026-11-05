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
    inputManager.bind(FUNKIN_ACTION::UI_LEFT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_LEFT});
    inputManager.bind(FUNKIN_ACTION::UI_DOWN, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_DOWN});
    inputManager.bind(FUNKIN_ACTION::UI_UP, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_UP});
    inputManager.bind(FUNKIN_ACTION::UI_RIGHT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_RIGHT});
    inputManager.bind(FUNKIN_ACTION::ACCEPT, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_RETURN});
    inputManager.bind(FUNKIN_ACTION::BACK, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_ESCAPE});
    inputManager.bind(FUNKIN_ACTION::PAUSE, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_RETURN});
    inputManager.bind(FUNKIN_ACTION::RESET, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_R});
    inputManager.bind(FUNKIN_ACTION::DEBUG_1, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_6});
    inputManager.bind(FUNKIN_ACTION::DEBUG_2, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_7});
    inputManager.bind(FUNKIN_ACTION::DEBUG_3, {INPUT_TYPE::KEYBOARD, SDL_SCANCODE_8});
}