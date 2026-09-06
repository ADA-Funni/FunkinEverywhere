#pragma once
#include <string>

struct SpriteRect 
{
    public:
        float x = 0;
        float y = 0;
        float w = 0;
        float h = 0;
};

class SpriteRenderParams
{
    public:
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;

        float scaleX = 1.0f;
        float scaleY = 1.0f;

        float alpha = 1.0f;
        float angle = 0.0f;
        float originX = 0.0f;
        float originY = 0.0f;
        bool flipX = false;
        bool flipY = false;
        std::string blend = "none";
};

class BaseSprite 
{
    protected:
		SpriteRect drect;
		SpriteRect srect;

    public:
        BaseSprite() = default;
        virtual void init(std::string path, std::string type = "none") = 0;
        virtual ~BaseSprite();

		SpriteRenderParams stuff;
        std::string spriteType;
		
        float frameX = 0.0f;
        float frameY = 0.0f;
        float frameWidth = 0.0f;
        float frameHeight = 0.0f;

        float getWidth();
        float getHeight();

        virtual void render();
};