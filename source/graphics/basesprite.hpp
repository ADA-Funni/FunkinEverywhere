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

    float fps = 24.0f;
    bool looped = false;
    bool flipX = false;
    bool flipY = false;
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

        float skewX = 0.0f;
        float skewY = 0.0f;

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

        float animTimer = 0.0f;
        bool animPlaying = false;

        float animFPS = 24.0f;
        bool animLoop = true;

    public:
        BaseSprite() = default;
        virtual void create(const std::string& path, const std::string& type = "none") = 0;
        virtual ~BaseSprite();

		SpriteRenderParams stuff;
        std::string spriteType;
		
        float frameX = 0.0f;
        float frameY = 0.0f;
        float frameWidth = 0.0f;
        float frameHeight = 0.0f;

        float getWidth();
        float getHeight();

        void update(float elapsed);
        virtual void render();

        std::string getAnimName(const std::string& frameName, int& frameIndex);
        void loadAtlas(const std::string& path);

        void addAnimFrames(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps, bool looped, bool flipX, bool flipY);

        void addAnim(const std::string& name, const std::string& prefix, float fps = 24.0f, bool looped = false, bool flipX = false, bool flipY = false);
        void addAnim(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps = 24.0f, bool looped = false, bool flipX = false, bool flipY = false);

        void playAnim(const std::string& name);
};