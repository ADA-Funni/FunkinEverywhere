#pragma once
#include <vector>
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#endif

class FunkinSound;

class SoundManager
{
    private:
        std::vector<FunkinSound*> dasounds;

    public:
        void init();
        
        void add(FunkinSound* sound);
        void remove(FunkinSound* sound);
        void clear();

        void update(float elapsed);

        #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        SDL_AudioDeviceID audioDevice;
        MIX_Mixer* mixer;
        MIX_Track* mtrack = nullptr;
        #endif
};

extern SoundManager sounds;