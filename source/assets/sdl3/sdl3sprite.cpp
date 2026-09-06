#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "../../rendering/sdl3/window.hpp"
#include "sdl3sprite.hpp"

void SDL3Sprite::init(std::string path, std::string type)
{
	this -> texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), path.c_str());
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

SDL3Sprite::SDL3Sprite(std::string path, std::string type)
{
	init(path, type);
}

void SDL3Sprite::render(SpriteRenderParams &params)
{
	float texWidth, texHeight;
	SDL_GetTextureSize(texture, &texWidth, &texHeight);

	params.srect.w = 500;
	params.srect.h = 500;

	params.drect.w = 500 * params.scaleX;
	params.drect.h = 500 * params.scaleY;

	SDL_FRect drect = {params.drect.x, params.drect.y, params.drect.w, params.drect.h};
	SDL_FRect srect = {params.srect.x, params.srect.y, params.srect.w, params.srect.h};

	SDL_RenderTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), texture, &srect, &drect);
}

SDL3Sprite::~SDL3Sprite()
{

}