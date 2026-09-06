#include <algorithm>
#include <iostream>
#include <vector>
#include <pugixml.hpp>

#include "basesprite.hpp"

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

void BaseSprite::playAnim(const std::string& name, float fps, bool loop)
{
    for (int i = 0; i < static_cast<int>(anims.size()); i++)
    {
        if (anims[i].name == name)
        {
            curAnim = i;
            curFrame = 0;

            animTimer = 0.0f;
            animFPS = fps;
            animLoop = loop;
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