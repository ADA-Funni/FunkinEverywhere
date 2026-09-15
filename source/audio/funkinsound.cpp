#include "funkinsound.hpp"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "sdl3/sdl3sound.hpp"
#endif

FunkinSound::FunkinSound(const std::string& path, const std::string& type)
{
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
    sound = std::make_unique<SDL3SoundFE>(path, type);
    #endif
}

void FunkinSound::update(float elapsed)
{
    sound -> update(elapsed);
}

void FunkinSound::play()
{
    sound -> play();
}

void FunkinSound::pause()
{
    sound -> pause();
}

void FunkinSound::playMusic()
{
    sound -> playMusic();
}

void FunkinSound::pauseMusic()
{
    sound -> pauseMusic();
}

void FunkinSound::stopMusic()
{
    sound -> stopMusic();
}