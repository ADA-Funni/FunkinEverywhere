#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "assets/sdl3/sdl3sprite.hpp"
#include "rendering/sdl3/window.hpp"

WindowFE *globalWindow = nullptr;

int windowWidth = 1280;
int windowHeight = 720;

BaseSprite *testSpr = nullptr;

int main(int argc, char **argv) 
{
    globalWindow = new WindowSDL3();
    if (!globalWindow -> init(windowWidth, windowHeight, "Funkin' Everywhere")) 
    {
        delete globalWindow;
        globalWindow = nullptr;
        return 1;
    }

    testSpr = new SDL3Sprite("assets/ui/title/logo-bumpin.png", "none");
    testSpr -> stuff.x = 0;

    while(!globalWindow -> shouldClose())
    {
        globalWindow -> pollEvents();
        globalWindow -> beginFrame(0, 0, 0, 0);
        testSpr -> render();
        globalWindow -> endFrame(true);
    }

    globalWindow -> cleanup();
    return 0;
}