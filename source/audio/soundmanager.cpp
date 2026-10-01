#include <algorithm>
#include <iostream>

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#endif

#include "soundmanager.hpp"
#include "basesound.hpp"

SoundManager sounds;

void SoundManager::init()
{
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
    if (!SDL_Init(SDL_INIT_AUDIO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return;
    }
    #endif
}

void SoundManager::add(FunkinSound* sound)
{
    dasounds.push_back(sound);
}

void SoundManager::remove(FunkinSound* sound)
{
    dasounds.erase(std::remove(dasounds.begin(), dasounds.end(), sound), dasounds.end());
}

void SoundManager::clear()
{
    for (FunkinSound* sound : dasounds) delete sound;
    dasounds.clear();
}

void SoundManager::update(float elapsed)
{
    for (FunkinSound* sound : dasounds)
    {
        sound -> update(elapsed);
    }
}