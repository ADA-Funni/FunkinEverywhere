#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

#include "../../rendering/sdl3/window.hpp"
#include "sdl3sprite.hpp"

void SDL3Sprite::init(const std::string& path, const std::string& type)
{
	if(type != "animateatlas" && type != "multianimate") 
	{
		texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), ("assets/" + path + ".png").c_str());
		if (type == "sparrow") loadAtlas("assets/" + path + ".xml");
	}

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

SDL3Sprite::SDL3Sprite(const std::string& path, const std::string& type)
{
	init(path, type);
	spriteType = type;
}

void SDL3Sprite::render()
{
    if (!texture) return;

    float texWidth, texHeight;
    SDL_GetTextureSize(texture, &texWidth, &texHeight);

    if (spriteType == "sparrow")
    {
        AtlasFrame& frame = anims[curAnim].frames[curFrame];

        srect.x = frame.x;
        srect.y = frame.y;
        srect.w = frame.width;
        srect.h = frame.height;

        frameX = frame.frameX;
        frameY = frame.frameY;
        frameWidth = frame.frameWidth;
        frameHeight = frame.frameHeight;

        stuff.width = frameWidth;
        stuff.height = frameHeight;
    }
    else
    {
        srect.x = 0;
        srect.y = 0;
        srect.w = texWidth;
        srect.h = texHeight;

        frameX = 0;
        frameY = 0;
        stuff.width = frameWidth = texWidth;
        stuff.height = frameHeight = texHeight;
    }

    drect.x = (stuff.x - frameX) * stuff.scaleX;
    drect.y = (stuff.y - frameY) * stuff.scaleY;
    drect.w = srect.w * stuff.scaleX;
    drect.h = srect.h * stuff.scaleY;

    SDL_FRect fdrect = {drect.x, drect.y, drect.w, drect.h};
    SDL_FRect fsrect = {srect.x, srect.y, srect.w, srect.h};

    SDL_RenderTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), texture, &fsrect, &fdrect);
}

SDL3Sprite::~SDL3Sprite()
{
	SDL_DestroyTexture(texture);
}