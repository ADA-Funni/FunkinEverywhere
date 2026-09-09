#pragma once
#include <string>

class WindowFE 
{
    public:
        virtual ~WindowFE() = default;

        bool debugMode = false;
        bool running = true;

        virtual bool create(int width, int height, const std::string &title) = 0;
        virtual float calcElapsed() = 0;
        virtual void destroy() = 0;

        virtual bool shouldClose() = 0;
        virtual void pollEvents() = 0;
        virtual void swapBuffers() = 0;
        virtual void resize(int width, int height) = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual float getPixelDensity() const = 0;
        virtual void *getHandle() = 0;

        float renderScale = 0;
        bool hasFrameBegan = false;

        virtual bool checkFramerate() = 0;
        virtual void setRenderScale() = 0;
        virtual void* getRenderer() = 0;

        virtual void beginFrame(int screen, int colorR, int colorG, int colorB) = 0;
        virtual void endFrame(bool shouldFlush = true) = 0;
};

extern std::string modName;
extern WindowFE *globalWindow;