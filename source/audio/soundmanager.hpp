#pragma once
#include <vector>
#include <dr_mp3.h>
#include <dr_wav.h>
#include <stb_vorbis.c>

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

        bool loadAsWAV();
        bool loadAsMP3();
        bool loadAsOGG();

        drwav wav;
        drmp3 mp3;
        stb_vorbis *ogg;
};

extern SoundManager sounds;