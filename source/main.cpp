#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "assets/funkinsprite.hpp"
#include "assets/spritemanager.hpp"
#include "rendering/sdl3/window.hpp"

WindowFE *globalWindow = nullptr;
SpriteManager sprites;

int windowWidth = 1280;
int windowHeight = 720;

int main(int argc, char **argv) 
{
    globalWindow = new WindowSDL3();
    if (!globalWindow -> init(windowWidth, windowHeight, "Funkin' Everywhere")) 
    {
        delete globalWindow;
        globalWindow = nullptr;
        return 1;
    }

    FunkinSprite* testSpr = new FunkinSprite("ui/title/logo-bumpin", "sparrow");
    testSpr -> getParams().x = 0;
    sprites.add(testSpr);

    testSpr -> playAnim("logo bumpin", 24, true);

    while(!globalWindow -> shouldClose())
    {
        float elapsed = globalWindow -> calcElapsed();

        sprites.update(elapsed);
        globalWindow -> pollEvents();
        globalWindow -> beginFrame(0, 0, 0, 0);
        sprites.render();
        globalWindow -> endFrame(true);
    }

    sprites.clear();
    globalWindow -> cleanup();

    return 0;
}