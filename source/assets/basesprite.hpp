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
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float alpha = 1.0f;
        float angle = 0.0f;
        float originX = 0.0f;
        float originY = 0.0f;
        bool flipX = false;
        bool flipY = false;
        std::string blend = "none";

        SpriteRect drect;
        SpriteRect srect;
};

struct SpriteData 
{
    public:
		int width = 0;
		int height = 0;
		std::string format = "none";
		int pitch = 0;
		void *pixels = nullptr;
		float scaleX = 1.0f;
		float scaleY = 1.0f;
};

class BaseSprite 
{
    protected:
        SpriteData sprData;

    public:
        BaseSprite() = default;
        virtual void init(std::string path, std::string type = "none");
        virtual ~BaseSprite();

        int getWidth();
        int getHeight();

        virtual void render(SpriteRenderParams &params);
};