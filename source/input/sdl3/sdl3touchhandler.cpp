#include "sdl3touchhandler.hpp"

#include <algorithm>

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
