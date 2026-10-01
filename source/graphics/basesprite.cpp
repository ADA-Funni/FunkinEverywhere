#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>
#include <pugixml.hpp>

#include "basesprite.hpp"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "sdl3/sdl3sprite.hpp"
#endif

std::string BaseSprite::getAnimName(const std::string& frameName, int& frameIndex)
{
    size_t pos = frameName.size();

    while (pos > 0 && std::isdigit(static_cast<unsigned char>(frameName[pos - 1]))) pos -= 1;
    if (pos == frameName.size())
    {
        frameIndex = 0;
        return frameName;
    }

    frameIndex = std::stoi(frameName.substr(pos));

    return frameName.substr(0, pos);
}

void BaseSprite::loadAtlas(const std::string& path)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    pugi::xml_node atlas = doc.child("TextureAtlas");

    for (pugi::xml_node node : atlas.children("SubTexture"))
    {
        AtlasFrame frame;

        frame.name = node.attribute("name").as_string();
        frame.x = node.attribute("x").as_float();
        frame.y = node.attribute("y").as_float();
        frame.width = node.attribute("width").as_float();
        frame.height = node.attribute("height").as_float();
        frame.frameX = node.attribute("frameX") ? node.attribute("frameX").as_float() : 0.0f;
        frame.frameY = node.attribute("frameY") ? node.attribute("frameY").as_float() : 0.0f;
        frame.frameWidth = node.attribute("frameWidth") ? node.attribute("frameWidth").as_float() : frame.width;
        frame.frameHeight = node.attribute("frameHeight") ? node.attribute("frameHeight").as_float() : frame.height;

        std::string animName = getAnimName(frame.name, frame.index);

        auto it = std::find_if(anims.begin(), anims.end(), [&](const Animation& anim) {return anim.name == animName;});

        if (it == anims.end())
        {
            Animation anim;

            anim.name = animName;
            anim.frames.push_back(frame);

            anims.push_back(anim);
        }
        else
        {
            it -> frames.push_back(frame);
        }
    }

    for (Animation& anim : anims)
    {
        std::sort(anim.frames.begin(), anim.frames.end(), [](const AtlasFrame& a, const AtlasFrame& b) {return a.index < b.index;});
    }

    if (!anims.empty() && !anims[0].frames.empty())
    {
        curAnim = 0;
        curFrame = 0;
    }
}

void BaseSprite::addAnimFrames(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps, bool looped, bool flipX, bool flipY)
{
    auto it = std::find_if(anims.begin(), anims.end(), [&](const Animation& anim) {return anim.name == prefix;});

    if (it == anims.end())
        return;

    Animation anim;

    anim.name = name;
    anim.frames.clear();

    for (int index : indices)
    {
        auto frameIt = std::find_if(it -> frames.begin(), it -> frames.end(), [&](const AtlasFrame& frame) {return frame.index == index;});
        if (frameIt != it -> frames.end()) anim.frames.push_back(*frameIt);
    }

    anim.fps = fps;
    anim.looped = looped;
    anim.flipX = flipX;
    anim.flipY = flipY;

    anims.push_back(anim);
}

void BaseSprite::addAnim(const std::string& name, const std::string& prefix, float fps, bool looped, bool flipX, bool flipY)
{
    auto it = std::find_if(anims.begin(), anims.end(), [&](const Animation& anim) {return anim.name == prefix;});

    if (it == anims.end()) return;

    Animation anim = *it;

    anim.name = name;
    anim.fps = fps;
    anim.looped = looped;
    anim.flipX = flipX;
    anim.flipY = flipY;

    anims.push_back(anim);
}

void BaseSprite::addAnim(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps, bool looped, bool flipX, bool flipY)
{
    addAnimFrames(name, prefix, indices, fps, looped, flipX, flipY);
}


void BaseSprite::playAnim(const std::string& name)
{
    for (int i = 0; i < static_cast<int>(anims.size()); i++)
    {
        if (anims[i].name == name)
        {
            curAnim = i;
            curFrame = 0;

            animTimer = 0.0f;
            animFPS = anims[i].fps;
            animLoop = anims[i].looped;
            animPlaying = true;

            return;
        }
    }
}

void BaseSprite::update(float elapsed)
{
    if (!animPlaying) return;
    if (curAnim < 0 || curAnim >= static_cast<int>(anims.size())) return;

    Animation& anim = anims[curAnim];
    if (anim.frames.empty()) return;

    animTimer += elapsed;
    float frameTime = 1.0f / animFPS;

    while (animTimer >= frameTime)
    {
        animTimer -= frameTime;
        curFrame += 1;

        if (curFrame >= static_cast<int>(anim.frames.size()))
        {
            if (animLoop)
            {
                curFrame = 0;
            }
            else
            {
                curFrame = anim.frames.size() - 1;
                animPlaying = false;
                break;
            }
        }
    }
}

BaseSprite::~BaseSprite() 
{
    
}

void BaseSprite::render() 
{
    
}

float BaseSprite::getWidth()
{
    return drect.w;
}

float BaseSprite::getHeight()
{
    return drect.h;
}

FunkinSprite::FunkinSprite(const std::string& path, const std::string& type)
{
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
    sprite = std::make_unique<SDL3Sprite>(path, type);
    #endif
}

void FunkinSprite::update(float elapsed)
{
    sprite -> update(elapsed);
}

void FunkinSprite::render()
{
    sprite -> render();
}

void FunkinSprite::addAnim(const std::string& name, const std::string& prefix, float fps, bool looped, bool flipX, bool flipY)
{
    sprite -> addAnim(name, prefix, fps, looped, flipX, flipY);
}

void FunkinSprite::addAnim(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps, bool looped, bool flipX, bool flipY)
{
    sprite -> addAnim(name, prefix, indices, fps, looped, flipX, flipY);
}

void FunkinSprite::playAnim(const std::string& name)
{
    sprite -> playAnim(name);
}

SpriteRenderParams& FunkinSprite::getParams()
{
    return sprite -> stuff;
}

float FunkinSprite::getWidth()
{
    return sprite -> getWidth();
}

float FunkinSprite::getHeight()
{
    return sprite -> getHeight();
}