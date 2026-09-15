#pragma once
#include <string>
#include <vector>

class BaseSound
{
    public:
        BaseSound() = default;
        virtual void create(const std::string& path, const std::string& type = "none") = 0;
        virtual ~BaseSound();
        
        std::string soundType;

        virtual void play();
        virtual void pause();

        virtual void playMusic();
        virtual void pauseMusic();
        virtual void stopMusic();

        virtual void update(float elapsed);
};