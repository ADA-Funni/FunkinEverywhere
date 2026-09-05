#include <SDL3/SDL.h>

#include <iostream>

#include "window.hpp"

bool WindowSDL3::init(int width, int height, const std::string &title)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        std::cerr << "Window/Renderer Creation Error: " << SDL_GetError() << std::endl;

        SDL_Quit();
        return false;
    }

    this->width = width;
    this->height = height;
    this->pixelDensity = SDL_GetWindowPixelDensity(window);

    return true;
}

void WindowSDL3::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool WindowSDL3::shouldClose()
{
    return shouldCloseFlag;
}

void WindowSDL3::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) 
        {
            case SDL_EVENT_QUIT:
            {
                shouldCloseFlag = true;
            } break;
            case SDL_EVENT_WINDOW_RESIZED: 
            {
                int w, h;
                SDL_GetWindowSizeInPixels(window, &w, &h);
                resize(w, h);
            } break;
        }
    }
}

void WindowSDL3::resize(int width, int height)
{
    this->width = width;
    this->height = height;
    this->pixelDensity = SDL_GetWindowPixelDensity(window);
}

int WindowSDL3::getWidth() const
{
    return width;
}

int WindowSDL3::getHeight() const
{
    return height;
}

float WindowSDL3::getPixelDensity() const
{
    return pixelDensity;
}

void *WindowSDL3::getHandle()
{
    return window;
}

void WindowSDL3::beginFrame(int screen, int colorR, int colorG, int colorB)
{
    running = !shouldCloseFlag;

    SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 255);
    SDL_RenderClear(renderer);

    hasFrameBegan = true;
}

void WindowSDL3::endFrame(bool shouldFlush)
{
    SDL_RenderPresent(renderer);

    hasFrameBegan = false;
}

void WindowSDL3::swapBuffers()
{
    return;
}

bool WindowSDL3::checkFramerate()
{
    return true;
}

void WindowSDL3::setRenderScale()
{
    return;
}

void WindowSDL3::renderSprites()
{
    return;
}

void *WindowSDL3::getRenderer()
{
    return renderer;
}