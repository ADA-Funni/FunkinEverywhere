#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <map>
#include <utility>
#include <vector>

#include "../inputmanager.hpp"

class InputManager;

class SDL3KeyboardHandler
{
    public:
        void handleEvent(const SDL_Event& event, InputManager& manager);
};

class SDL3ControllerHandler
{
    private:
        std::map<SDL_JoystickID, SDL_Gamepad*> controllers;
        std::map<SDL_JoystickID, std::array<bool, SDL_GAMEPAD_AXIS_COUNT * 2>> axisStates;

        static constexpr Sint16 AXIS_PRESS_THRESHOLD = 16000;
        static constexpr Sint16 AXIS_RELEASE_THRESHOLD = 12000;

        void openController(SDL_JoystickID id);
        void closeController(SDL_JoystickID id, InputManager& manager);

        void updateAxis(SDL_JoystickID id, SDL_GamepadAxis axis, Sint16 value, InputManager& manager);

    public:
        ~SDL3ControllerHandler();

        void init(InputManager& manager);
        void handleEvent(const SDL_Event& event, InputManager& manager);
};

class SDL3TouchHandler
{
    private:
        using FingerKey = std::pair<SDL_TouchID, SDL_FingerID>;

        std::vector<TouchRegion> regions;
        std::map<FingerKey, int> fingers;

        int findRegion(float x, float y) const;
        int fingerCount(int region) const;
        void updateFinger(FingerKey finger, float x, float y, InputManager& manager);
        void releaseFinger(FingerKey finger, InputManager& manager);

    public:
        int addRegion(TouchRegion region, InputManager& manager);
        void clearRegions(InputManager& manager);
        void handleEvent(const SDL_Event& event, InputManager& manager);
};