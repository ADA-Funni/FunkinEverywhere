#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <string>
#include <iostream>

#include "../../rendering/sdl3/window.hpp"
#include "../../rendering/window.hpp"
#include "sdl3sprite.hpp"
#include "../../util/coolutil.hpp"

void SDL3Sprite::create(const std::string& path, const std::string& type)
{
    auto mods = listDirectory("mods");
    modName = (mods && !mods -> empty()) ? (*mods)[0] : "none";

	if(type != "animateatlas" && type != "multianimate") 
	{
        std::string assetPath = fileExists("mods/" + modName + "/" + path + ".png") ? "mods/" + modName + "/" : "assets/";
		texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), (assetPath + path + ".png").c_str());
		if (type == "sparrow") loadAtlas(assetPath + path + ".xml");
	}

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

SDL3Sprite::SDL3Sprite(const std::string& path, const std::string& type)
{
	spriteType = type;
	create(path, type);
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

    float u0 = srect.x / texWidth;
    float v0 = srect.y / texHeight;

    float u1 = (srect.x + srect.w) / texWidth;
    float v1 = (srect.y + srect.h) / texHeight;

    float rad = stuff.angle * (std::acos(-1.0f) / 180.0f);
    float cosA = cosf(rad);
    float sinA = sinf(rad);

    float centerX = drect.x + (drect.w / 2.0f);
    float centerY = drect.y + (drect.h / 2.0f);

    SDL_FPoint p_tl = {(drect.x + (stuff.skewX / 2.0f)) - centerX, (drect.y + (stuff.skewY / 2.0f)) - centerY};
    SDL_FPoint p_tr = {((drect.x + drect.w) + (stuff.skewX / 2.0f)) - centerX, (drect.y - (stuff.skewY / 2.0f)) - centerY};
    SDL_FPoint p_br = {((drect.x + drect.w) - (stuff.skewX / 2.0f)) - centerX, ((drect.y + drect.h) - (stuff.skewY / 2.0f)) - centerY};
    SDL_FPoint p_bl = {(drect.x - (stuff.skewX / 2.0f)) - centerX, ((drect.y + drect.h) + (stuff.skewY / 2.0f)) - centerY};

    SDL_Vertex vertices[4] = {
        {{centerX + (p_tl.x * cosA - p_tl.y * sinA), centerY + (p_tl.x * sinA + p_tl.y * cosA)}, {1.0f, 1.0f, 1.0f, 1.0f}, {u0, v0}}, // tl
        {{centerX + (p_tr.x * cosA - p_tr.y * sinA), centerY + (p_tr.x * sinA + p_tr.y * cosA)}, {1.0f, 1.0f, 1.0f, 1.0f}, {u1, v0}}, // tr
        {{centerX + (p_br.x * cosA - p_br.y * sinA), centerY + (p_br.x * sinA + p_br.y * cosA)}, {1.0f, 1.0f, 1.0f, 1.0f}, {u1, v1}}, // br
        {{centerX + (p_bl.x * cosA - p_bl.y * sinA), centerY + (p_bl.x * sinA + p_bl.y * cosA)}, {1.0f, 1.0f, 1.0f, 1.0f}, {u0, v1}} // bl
    };

    int daindices[6] = {0, 1, 2, 2, 3, 0};

    SDL_FRect fdrect = {drect.x, drect.y, drect.w, drect.h};
    SDL_FRect fsrect = {srect.x, srect.y, srect.w, srect.h};

    SDL_RenderGeometry(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), texture, vertices, 4, daindices, 6);
}

SDL3Sprite::~SDL3Sprite()
{
	SDL_DestroyTexture(texture);
}