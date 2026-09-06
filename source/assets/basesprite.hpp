#pragma once
#include <string>
#include <vector>

struct SpriteRect 
{
    public:
        float x = 0.0f;
        float y = 0.0f;
        float w = 0.0f;
        float h = 0.0f;
};

struct AtlasFrame
{
    std::string name;
    int index = 0;

    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    float frameX = 0.0f;
    float frameY = 0.0f;
    float frameWidth = 0.0f;
    float frameHeight = 0.0f;
};

struct Animation
{
    std::string name;
    std::vector<AtlasFrame> frames;
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

        std::vector<Animation> anims;

        int curAnim = 0;
        int curFrame = 0;

    public:
        BaseSprite() = default;
        virtual void init(const std::string& path, const std::string& type = "none") = 0;
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

        std::string getAnimName(const std::string& frameName, int& frameIndex);
        void loadAtlas(const std::string& path);
};