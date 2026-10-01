#pragma once
#include <memory>
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

class FunkinSound
{
    friend class SoundManager;

    private:
        std::unique_ptr<BaseSound> sound;

    public:
        FunkinSound(const std::string& path, const std::string& type = "none");

        void play();
        void pause();

        void playMusic();
        void pauseMusic();
        void stopMusic();

        void update(float elapsed);
};