#include <algorithm>

#include "soundmanager.hpp"
#include "funkinsound.hpp"

SoundManager sounds;

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

void SoundManager::render()
{
    for (FunkinSound* sound : dasounds)
    {
        sound -> render();
    }
}