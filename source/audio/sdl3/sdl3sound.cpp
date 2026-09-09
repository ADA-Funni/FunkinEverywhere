#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

#include "sdl3sound.hpp"
#include "../soundmanager.hpp"
#include "../../util/coolutil.hpp"
#include "../../rendering/window.hpp"

void SDL3SoundFE::create(const std::string& path, const std::string& type)
{
    auto mods = listDirectory("mods");
    modName = (mods && !mods -> empty()) ? (*mods)[0] : "none";
    std::string assetPath = fileExists("mods/" + modName + "/" + path + ".ogg") ? "mods/" + modName + "/" : "assets/";

    sound = MIX_LoadAudio(NULL, (assetPath + path + ".ogg").c_str(), false);
    if (!sound)
    {
        std::cout << "MIX_LoadAudio failed: " << SDL_GetError() << std::endl;
    }
    if(type == "music")
    {
        MIX_SetTrackAudio(sounds.mtrack, sound);
    }
    else
    {
        strack = MIX_CreateTrack(sounds.mixer);
        MIX_SetTrackAudio(strack, sound);
    }
}

SDL3SoundFE::SDL3SoundFE(const std::string& path, const std::string& type)
{
    create(path, type);
    soundType = type;
}

SDL3SoundFE::~SDL3SoundFE()
{
    MIX_DestroyAudio(sound);
}

void SDL3SoundFE::play()
{
    MIX_PlayTrack(strack, 0);
}

void SDL3SoundFE::playMusic()
{
    MIX_PlayTrack(sounds.mtrack, 0);
}

void SDL3SoundFE::stopMusic()
{
    MIX_StopTrack(sounds.mtrack, 0);
}

void SDL3SoundFE::update(float elapsed)
{

}