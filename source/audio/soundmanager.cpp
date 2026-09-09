#include <algorithm>
#include <iostream>

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#endif

#include "soundmanager.hpp"
#include "funkinsound.hpp"

SoundManager sounds;

void SoundManager::init()
{
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
    if (!SDL_Init(SDL_INIT_AUDIO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    if (!MIX_Init())
    {
        std::cerr << "MIX_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!audioDevice)
    {
        std::cerr << "SDL_OpenAudioDevice Error: " << SDL_GetError() << std::endl;
        return;
    }

    mixer = MIX_CreateMixerDevice(audioDevice, NULL);
    if (!mixer)
    {
        std::cerr << "MIX_CreateMixerDevice Error: " << SDL_GetError() << std::endl;
        return;
    }

    mtrack = MIX_CreateTrack(mixer);
    if (!mtrack)
    {
        std::cerr << "MIX_CreateTrack Error: " << SDL_GetError() << std::endl;
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