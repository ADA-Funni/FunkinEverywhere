#include <pugixml.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "../../rendering/sdl3/window.hpp"
#include "sdl3sprite.hpp"

void SDL3Sprite::init(std::string path, std::string type)
{
	texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), path.c_str());
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

SDL3Sprite::SDL3Sprite(std::string path, std::string type)
{
	init(path, type);
	spriteType = type;
}

void SDL3Sprite::render()
{
	float texWidth, texHeight;
	SDL_GetTextureSize(texture, &texWidth, &texHeight);

	stuff.width = texWidth;
	stuff.height = texHeight;

	if(spriteType == "sparrow")
	{

	}
	else
	{
		frameWidth = texWidth;
		frameHeight = texHeight;
	}

	srect.x = frameX;
	srect.y = frameY;
	srect.w = frameWidth;
	srect.h = frameHeight;

	drect.x = stuff.x;
	drect.y = stuff.y;
	drect.w = stuff.width * stuff.scaleX;
	drect.h = stuff.height * stuff.scaleY;

	SDL_FRect fdrect = {drect.x, drect.y, drect.w, drect.h};
	SDL_FRect fsrect = {srect.x, srect.y, srect.w, srect.h};

	SDL_RenderTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), texture, &fsrect, &fdrect);
}

SDL3Sprite::~SDL3Sprite()
{
	SDL_DestroyTexture(texture);
}