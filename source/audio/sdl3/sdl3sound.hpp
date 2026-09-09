#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
#include <string>
#include <vector>

#include "../basesound.hpp"

class SDL3SoundFE : public BaseSound // SDL3Sound already exists
{
    private:
        MIX_Audio* sound = nullptr;
        MIX_Track* strack = nullptr;

    public:
        SDL3SoundFE(const std::string& path, const std::string& type = "none");
        void create(const std::string& path, const std::string& type = "none") override;
        ~SDL3SoundFE() override;

        void play();
        void playMusic();
        void stopMusic();

        void update(float elapsed);
};