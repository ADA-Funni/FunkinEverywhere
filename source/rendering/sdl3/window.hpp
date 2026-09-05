#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "../window.hpp"

class WindowSDL3 : public WindowFE 
{
  public:
    bool debugMode;
    bool running;

    bool init(int width, int height, const std::string &title);
    void cleanup();

    bool shouldClose();
    void pollEvents();
    void swapBuffers();
    void resize(int width, int height);

    int getWidth() const;
    int getHeight() const;
    float getPixelDensity() const;
    void *getHandle();
    
    float renderScale;
    bool hasFrameBegan;

    bool checkFramerate();

    void setRenderScale();
    void renderSprites();

    void *getRenderer();

    void beginFrame(int screen, int colorR, int colorG, int colorB);
    void endFrame(bool shouldFlush = true);

  private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_GLContext context = nullptr;
    int width = 0;
    int height = 0;
    float pixelDensity = 1.0f;
    bool shouldCloseFlag = false;
};