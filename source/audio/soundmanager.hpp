#pragma once
#include <vector>

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

        int current_position_seconds;
};

extern SoundManager sounds;