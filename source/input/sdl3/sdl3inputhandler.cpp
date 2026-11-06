#include "sdl3inputhandler.hpp"
#include <algorithm>

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

int SDL3TouchHandler::addRegion(TouchRegion region, InputManager& manager)
{
    int index = static_cast<int>(regions.size());
    regions.push_back(region);

    manager.bind(region.action, {INPUT_TYPE::TOUCH, index, 0});

    return index;
}

void SDL3TouchHandler::clearRegions(InputManager& manager)
{
    for (int i = 0; i < static_cast<int>(regions.size()); i++)
    {
        manager.unbind(regions[i].action, {INPUT_TYPE::TOUCH, i, 0});
    }

    manager.releaseAll(INPUT_TYPE::TOUCH);

    regions.clear();
    fingers.clear();
}

int SDL3TouchHandler::findRegion(float x, float y) const
{
    for (int i = 0; i < static_cast<int>(regions.size()); i++)
    {
        const auto& region = regions[i];

        if (x >= region.x && y >= region.y && x <= region.x + region.width && y <= region.y + region.height)
        {
            return i;
        }
    }

    return -1;
}

int SDL3TouchHandler::fingerCount(int region) const
{
    return static_cast<int>(std::count_if(fingers.begin(), fingers.end(), [region](const auto& finger) {return finger.second == region;}));
}

void SDL3TouchHandler::updateFinger(FingerKey finger, float x, float y, InputManager& manager)
{
    int newRegion = findRegion(x, y);
    auto it = fingers.find(finger);
    int oldRegion = it != fingers.end() ? it->second : -1;
    if (oldRegion == newRegion) return;

    if (oldRegion != -1)
    {
        fingers.erase(finger);

        if (fingerCount(oldRegion) == 0)
        {
            manager.setInput({INPUT_TYPE::TOUCH, oldRegion, 0}, false);
        }
    }

    if (newRegion != -1)
    {
        bool wasInactive = fingerCount(newRegion) == 0;
        fingers[finger] = newRegion;

        if (wasInactive)
        {
            manager.setInput({INPUT_TYPE::TOUCH, newRegion, 0}, true);
        }
    }
}

void SDL3TouchHandler::releaseFinger(FingerKey finger, InputManager& manager)
{
    auto it = fingers.find(finger);
    if (it == fingers.end()) return;

    int region = it -> second;
    fingers.erase(it);

    if (fingerCount(region) == 0)
    {
        manager.setInput({INPUT_TYPE::TOUCH, region, 0}, false);
    }
}

void SDL3TouchHandler::handleEvent(const SDL_Event& event, InputManager& manager)
{
    switch (event.type)
    {
        case SDL_EVENT_FINGER_DOWN:
        case SDL_EVENT_FINGER_MOTION:
        {
            updateFinger({event.tfinger.touchID, event.tfinger.fingerID}, event.tfinger.x, event.tfinger.y, manager);
            break;
        }

        case SDL_EVENT_FINGER_UP:
        {
            releaseFinger({event.tfinger.touchID, event.tfinger.fingerID}, manager);
            break;
        }

        case SDL_EVENT_WINDOW_FOCUS_LOST:
        {
            manager.releaseAll(INPUT_TYPE::TOUCH);
            fingers.clear();
            break;
        }
    }
}