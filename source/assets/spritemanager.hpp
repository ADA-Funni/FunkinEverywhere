#pragma once
#include <vector>

class FunkinSprite;

class SpriteManager
{
    private:
        std::vector<FunkinSprite*> dasprites;

    public:
        void add(FunkinSprite* sprite);
        void remove(FunkinSprite* sprite);
        void clear();

        void update(float elapsed);
        void render();
};

extern SpriteManager sprites;