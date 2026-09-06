#pragma once
#include <vector>

#include "funkinsprite.hpp"

class FunkinSprite;

class SpriteManager
{
    private:
        std::vector<FunkinSprite*> sprites;

    public:
        void add(FunkinSprite* sprite);
        void remove(FunkinSprite* sprite);
        void clear();

        void update(float elapsed);
        void render();
};