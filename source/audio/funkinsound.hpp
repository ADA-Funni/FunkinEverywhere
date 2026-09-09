#pragma once
#include <memory>
#include <string>
#include <vector>

#include "basesound.hpp"

class FunkinSound
{
    friend class SoundManager;

    private:
        std::unique_ptr<BaseSound> sound;

    public:
        FunkinSound(const std::string& path, const std::string& type = "none");

        void play();
        void playMusic();
        void stopMusic();

        void update(float elapsed);
};