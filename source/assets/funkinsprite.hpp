#pragma once
#include <memory>
#include <string>

#include "basesprite.hpp"

class FunkinSprite
{
    friend class SpriteManager;

    private:
        std::unique_ptr<BaseSprite> sprite;

    public:
        FunkinSprite(const std::string& path, const std::string& type = "none");

        void update(float elapsed);
        void render();

        void addAnim(const std::string& name, const std::string& prefix, float fps = 24.0f, bool looped = false, bool flipX = false, bool flipY = false);
        void addAnim(const std::string& name, const std::string& prefix, const std::vector<int>& indices, float fps = 24.0f, bool looped = false, bool flipX = false, bool flipY = false);

        void playAnim(const std::string& name);

        SpriteRenderParams& getParams();

        float getWidth();
        float getHeight();
};