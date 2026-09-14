#include <SDL3/SDL.h>
#include <string>
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

    
}

SDL3SoundFE::SDL3SoundFE(const std::string& path, const std::string& type)
{
    create(path, type);
    soundType = type;
}

SDL3SoundFE::~SDL3SoundFE()
{
    
}

void SDL3SoundFE::play()
{
    
}

void SDL3SoundFE::playMusic()
{
    
}

void SDL3SoundFE::stopMusic()
{
    
}

void SDL3SoundFE::update(float elapsed)
{

}