#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "assets/spritemanager.hpp"
#include "rendering/sdl3/window.hpp"
#include "funkin/states/titlestate.hpp"
#include "funkin/conductor.hpp"

WindowFE *globalWindow = nullptr;
StateManager states;

int windowWidth = 1280;
int windowHeight = 720;

int main(int argc, char **argv) 
{
    globalWindow = new WindowSDL3();
    if (!globalWindow -> create(windowWidth, windowHeight, "Funkin' Everywhere")) 
    {
        delete globalWindow;
        globalWindow = nullptr;
        return 1;
    }

    TitleState *initialState = new TitleState(); // replace this line if you wanna have a different initial state
    states.changeState(initialState);

    while(!globalWindow -> shouldClose())
    {
        float elapsed = globalWindow -> calcElapsed();

        sprites.update(elapsed);
        conductor.updateBeats(elapsed);
        states.update(elapsed);
        globalWindow -> pollEvents();
        globalWindow -> beginFrame(0, 0, 0, 0);
        sprites.render();
        globalWindow -> endFrame(true);
    }

    sprites.clear();
    globalWindow -> destroy();

    return 0;
}