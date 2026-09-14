#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <vector>

#include "../basesound.hpp"

class SDL3SoundFE : public BaseSound
{
    public:
        SDL3SoundFE(const std::string& path, const std::string& type = "none");
        void create(const std::string& path, const std::string& type = "none") override;
        ~SDL3SoundFE() override;

        void play();
        void pause();

        void playMusic();
        void pauseMusic();
        void stopMusic();

        void update(float elapsed);
    private:
        SDL_AudioStream* stream;
};