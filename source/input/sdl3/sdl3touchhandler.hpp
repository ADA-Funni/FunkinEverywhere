#pragma once

#include <SDL3/SDL.h>

#include <map>
#include <utility>
#include <vector>

#include "../inputmanager.hpp"

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