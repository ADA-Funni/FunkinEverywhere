#pragma once
#include <vector>

class FunkinSound;

class SoundManager
{
    private:
        std::vector<FunkinSound*> dasounds;

    public:
        void add(FunkinSound* sound);
        void remove(FunkinSound* sound);
        void clear();

        void update(float elapsed);
        void render();
};

extern SoundManager sounds;