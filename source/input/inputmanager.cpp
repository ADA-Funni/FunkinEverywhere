#include <algorithm>
#include "inputmanager.hpp"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include <SDL3/SDL.h>
#include "sdl3/sdl3input.hpp"
#endif

void InputManager::init()
{
    clear();
}

void InputManager::setInput(PhysicalInput input, bool pressed)
{
    auto it = std::find(activeInputs.begin(), activeInputs.end(), input);

    if (pressed)
    {
        if (it != activeInputs.end()) return;
        activeInputs.push_back(input);
    }
    else
    {
        if (it == activeInputs.end()) return;
        activeInputs.erase(it);
    }

    refreshStates();
}

void InputManager::releaseAll(INPUT_TYPE type)
{
    activeInputs.erase(std::remove_if(activeInputs.begin(), activeInputs.end(), [type](const PhysicalInput& input) {return input.type == type;}), activeInputs.end());
    refreshStates();
}

void InputManager::refreshStates()
{
    for (int i = 0; i < static_cast<int>(FUNKIN_ACTION::COUNT); i++)
    {
        auto& state = states[i];
        bool isPressed = false;

        for (const auto& keybind : keybinds)
        {
            if (static_cast<int>(keybind.action) != i) continue;

            for (const auto& input : keybind.inputs)
            {
                for (const auto& active : activeInputs)
                {
                    if (input.type == active.type && input.code == active.code && (input.device == -1 || input.device == active.device))
                    {
                        isPressed = true;
                        break;
                    }
                }

                if (isPressed) break;
            }

            if (isPressed) break;
        }

        if (state.pressed != isPressed)
        {
            if (isPressed) state.justPressed = true; else state.justReleased = true;
        }

        state.pressed = isPressed;
    }
}

void InputManager::update()
{
    for (auto& state : states)
    {
        state.justPressed = false;
        state.justReleased = false;
    }
}

bool InputManager::pressed(FUNKIN_ACTION action)
{
    return states[static_cast<int>(action)].pressed;
}

bool InputManager::justPressed(FUNKIN_ACTION action)
{
    return states[static_cast<int>(action)].justPressed;
}

bool InputManager::justReleased(FUNKIN_ACTION action)
{
    return states[static_cast<int>(action)].justReleased;
}

void InputManager::bind(FUNKIN_ACTION action, PhysicalInput input)
{
    for (auto& keybind : keybinds)
    {
        if (keybind.action != action) continue;

        if (std::find(keybind.inputs.begin(), keybind.inputs.end(), input) == keybind.inputs.end())
        {
            keybind.inputs.push_back(input);
        }

        refreshStates();
        return;
    }

    keybinds.push_back({action, {input}});
    refreshStates();
}

void InputManager::unbind(FUNKIN_ACTION action, PhysicalInput input)
{
    for (auto& keybind : keybinds)
    {
        if (keybind.action != action) continue;

        auto& inputs = keybind.inputs;
        inputs.erase(std::remove(inputs.begin(), inputs.end(), input), inputs.end());
    }

    keybinds.erase(std::remove_if(keybinds.begin(), keybinds.end(), [](const Keybind& keybind) {return keybind.inputs.empty();}), keybinds.end());
    refreshStates();
}

void InputManager::clear()
{
    keybinds.clear();
    activeInputs.clear();

    for (auto& state : states) state = {};
}

InputManager inputManager;