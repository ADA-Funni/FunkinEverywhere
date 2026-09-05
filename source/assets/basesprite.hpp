#pragma once
#include <string>

class SpriteRenderParams
{
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

    ImageSubrect *subrect = nullptr;
}

struct SpriteData 
{
    int width = 0;
    int height = 0;
    std::string format = "none";
    int pitch = 0;
    void *pixels = nullptr;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
};

struct SpriteSubrect 
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

class BaseSprite 
{
  protected:
    SpriteData sprData;

  public:
    virtual bool BaseSprite(std::string tag, std::string path, std::string type) = 0;
    nonstd::expected<void, std::string> init(std::string tag, std::string path, std::string type = "none");
    virtual ~BaseSprite() = default;

    int getWidth();
    int getHeight();

    virtual void render(SpriteRenderParams &params) = 0;
};