#include "sdl3controllerhandler.hpp"
#include "../inputmanager.hpp"
#include <SDL3/SDL.h>

SDL3ControllerHandler::~SDL3ControllerHandler()
{
    for (auto& [id, controller] : controllers)
    {
        SDL_CloseGamepad(controller);
    }

    controllers.clear();
}

void SDL3ControllerHandler::openController(SDL_JoystickID id)
{
    if (controllers.find(id) != controllers.end()) return;

    SDL_Gamepad* controller = SDL_OpenGamepad(id);
    if (!controller) return;

    controllers[id] = controller;
    axisStates[id] = {};
}

void SDL3ControllerHandler::closeController(SDL_JoystickID id, InputManager& manager)
{
    auto it = controllers.find(id);
    if (it == controllers.end()) return;

    for (int i = 0; i < static_cast<int>(SDL_GAMEPAD_BUTTON_COUNT); i++)
    {
        manager.setInput({INPUT_TYPE::CONTROLLER_BUTTON, i, id}, false);
    }

    for (int i = 0; i < SDL_GAMEPAD_AXIS_COUNT * 2; i++)
    {
        manager.setInput({INPUT_TYPE::CONTROLLER_AXIS, i, id}, false);
    }

    SDL_CloseGamepad(it -> second);

    controllers.erase(it);
    axisStates.erase(id);
}

void SDL3ControllerHandler::init(InputManager& manager)
{
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    if (!ids) return;

    for (int i = 0; i < count; i++) openController(ids[i]);
    SDL_free(ids);
}

void SDL3ControllerHandler::updateAxis(SDL_JoystickID id, SDL_GamepadAxis axis, Sint16 value, InputManager& manager)
{
    int axisIndex = static_cast<int>(axis);
    if (axisIndex < 0 || axisIndex >= SDL_GAMEPAD_AXIS_COUNT) return;

    auto& states = axisStates[id];

    for (int direction = 0; direction < 2; direction++)
    {
        bool positive = direction == 1;

        if ((axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER || axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) && !positive)
        {
            continue;
        }

        int code = axisIndex * 2 + direction;
        int stateIndex = code;
        bool wasPressed = states[stateIndex];
        int magnitude = positive ? value : -static_cast<int>(value);

        bool isPressed = wasPressed ? magnitude > AXIS_RELEASE_THRESHOLD : magnitude > AXIS_PRESS_THRESHOLD;
        if (wasPressed != isPressed)
        {
            states[stateIndex] = isPressed;
            manager.setInput({INPUT_TYPE::CONTROLLER_AXIS, code, id}, isPressed);
        }
    }
}

void SDL3ControllerHandler::handleEvent(const SDL_Event& event, InputManager& manager)
{
    switch (event.type)
    {
        case SDL_EVENT_GAMEPAD_ADDED:
        {
            openController(event.gdevice.which);
            break;
        }

        case SDL_EVENT_GAMEPAD_REMOVED:
        {
            closeController(event.gdevice.which, manager);
            break;
        }

        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        {
            manager.setInput({INPUT_TYPE::CONTROLLER_BUTTON, static_cast<int>(event.gbutton.button), event.gbutton.which}, true);
            break;
        }

        case SDL_EVENT_GAMEPAD_BUTTON_UP:
        {
            manager.setInput({INPUT_TYPE::CONTROLLER_BUTTON, static_cast<int>(event.gbutton.button), event.gbutton.which}, false);
            break;
        }

        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        {
            updateAxis(event.gaxis.which, static_cast<SDL_GamepadAxis>(event.gaxis.axis), event.gaxis.value, manager);
            break;
        }

        case SDL_EVENT_WINDOW_FOCUS_LOST:
        {
            manager.releaseAll(INPUT_TYPE::CONTROLLER_BUTTON);
            manager.releaseAll(INPUT_TYPE::CONTROLLER_AXIS);
            axisStates.clear();

            for (const auto& [id, controller] : controllers) axisStates[id] = {};

            break;
        }
    }
}