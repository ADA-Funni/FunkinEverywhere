#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

#include "../../rendering/sdl3/window.hpp"
#include "../../rendering/window.hpp"
#include "sdl3sprite.hpp"
#include "../../util/coolutil.hpp"
#include "../basesprite.hpp"

namespace
{
    AffineMatrix composeMatrix(const AffineMatrix& parent, const AffineMatrix& child)
    {
        AffineMatrix result;

        result.a = parent.a * child.a + parent.c * child.b;
        result.b = parent.b * child.a + parent.d * child.b;
        result.c = parent.a * child.c + parent.c * child.d;
        result.d = parent.b * child.c + parent.d * child.d;
        result.tx = parent.a * child.tx + parent.c * child.ty + parent.tx;
        result.ty = parent.b * child.tx + parent.d * child.ty + parent.ty;

        return result;
    }
}

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
	else
	{
        std::string assetPath = fileExists("mods/" + modName + "/" + path + "/spritemap1.png") ? "mods/" + modName + "/" : "assets/";
		texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), (assetPath + path + "/spritemap1.png").c_str());
		loadSpritemap(assetPath + path);
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
    if (!stuff.visible) return;
    if (!texture) return;

    if (spriteType == "animateatlas" || spriteType == "multianimate")
    {
        if (curAnim < 0 || curAnim >= static_cast<int>(anims.size())) return;

        const Animation& animation = anims[curAnim];
        if (animation.frames.empty() || curFrame < 0 || curFrame >= static_cast<int>(animation.frames.size())) return;

        renderSpritemap(animation.frames[curFrame].index);
        return;
    }

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

    float u0 = 0.0f;
    float u1 = 0.0f;
    float v0 = 0.0f;
    float v1 = 0.0f;

    if (stuff.flipX)
    {
        u0 = (srect.x + srect.w) / texWidth;
        u1 = srect.x / texWidth;
    }
    else
    {
        u0 = srect.x / texWidth;
        u1 = (srect.x + srect.w) / texWidth;
    }

    if (stuff.flipY)
    {
        v0 = (srect.y + srect.h) / texHeight;
        v1 = srect.y / texHeight;
    }
    else
    {
        v0 = srect.y / texHeight;
        v1 = (srect.y + srect.h) / texHeight;
    }

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
        {{centerX + (p_tl.x * cosA - p_tl.y * sinA), centerY + (p_tl.x * sinA + p_tl.y * cosA)}, {stuff.color.r, stuff.color.g, stuff.color.b, stuff.alpha}, {u0, v0}},
        {{centerX + (p_tr.x * cosA - p_tr.y * sinA), centerY + (p_tr.x * sinA + p_tr.y * cosA)}, {stuff.color.r, stuff.color.g, stuff.color.b, stuff.alpha}, {u1, v0}},
        {{centerX + (p_br.x * cosA - p_br.y * sinA), centerY + (p_br.x * sinA + p_br.y * cosA)}, {stuff.color.r, stuff.color.g, stuff.color.b, stuff.alpha}, {u1, v1}},
        {{centerX + (p_bl.x * cosA - p_bl.y * sinA), centerY + (p_bl.x * sinA + p_bl.y * cosA)}, {stuff.color.r, stuff.color.g, stuff.color.b, stuff.alpha}, {u0, v1}}
    };

    int daindices[6] = {0, 1, 2, 2, 3, 0};

    SDL_RenderGeometry(static_cast<SDL_Renderer*>(globalWindow -> getRenderer()), texture, vertices, 4, daindices, 6);
}

void SDL3Sprite::renderSpritemap(int frame)
{
    if (spritemapData.rootSymbolName.empty()) return;

    auto rootIt = spritemapData.symbols.find(spritemapData.rootSymbolName);
    if (rootIt == spritemapData.symbols.end()) return;

    const int rootDuration = rootIt->second.duration();
    if (rootDuration <= 0) return;

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();

    bool hasBounds = false;

    // I'm prolly gonna rewrite this as its very messy and redundant
    std::function<void(const std::string&, int, const AffineMatrix&, int)> calculateBounds;

    calculateBounds = [&](const std::string& symbolName, int symbolFrame, const AffineMatrix& parentMatrix, int recursionDepth)
    {
        if (recursionDepth >= 32) return;

        auto symbolIt = spritemapData.symbols.find(symbolName);
        if (symbolIt == spritemapData.symbols.end()) return;

        const SpritemapSymbol& symbol = symbolIt->second;

        for (int layerIndex = static_cast<int>(symbol.layers.size()) - 1; layerIndex >= 0; --layerIndex)
        {
            const SpritemapKeyframe* keyframe = symbol.getKeyframe(layerIndex, symbolFrame);

            if (!keyframe) continue;

            for (const SpritemapElement& element : keyframe->elements)
            {
                if (element.isAtlasSprite)
                {
                    const AffineMatrix matrix = composeMatrix(parentMatrix, element.asi.mx);
                    auto pieceIt = spritemapData.atlas.find(element.asi.pieceName);
                    if (pieceIt == spritemapData.atlas.end()) continue;

                    const SpritemapPiece& piece = pieceIt->second;

                    const float width = static_cast<float>(piece.rotated ? piece.h : piece.w);
                    const float height = static_cast<float>(piece.rotated ? piece.w : piece.h);
                    if (width <= 0.0f || height <= 0.0f) continue;

                    const float px[4] = {0.0f, width, width, 0.0f};
                    const float py[4] = {0.0f, 0.0f, height, height};

                    for (int i = 0; i < 4; ++i)
                    {
                        const float x = matrix.a * px[i] + matrix.c * py[i] + matrix.tx;
                        const float y = matrix.b * px[i] + matrix.d * py[i] + matrix.ty;

                        minX = std::min(minX, x);
                        minY = std::min(minY, y);
                        maxX = std::max(maxX, x);
                        maxY = std::max(maxY, y);

                        hasBounds = true;
                    }
                }
                else
                {
                    auto childIt = spritemapData.symbols.find(element.si.symbolName);
                    if (childIt == spritemapData.symbols.end()) continue;

                    const SpritemapSymbol& child = childIt->second;
                    const int childDuration = child.duration();
                    if (childDuration <= 0) continue;

                    AffineMatrix childMatrix = composeMatrix(parentMatrix, element.si.mx);
                    int childFrame = element.si.firstFrame + (symbolFrame - keyframe->index);

                    const std::string& loopType = element.si.loopType;
                    const bool loops = loopType == "LOOP" || loopType == "loop" || loopType == "1";

                    if (loops)
                    {
                        childFrame %= childDuration;
                        if (childFrame < 0) childFrame += childDuration;
                    }
                    else
                    {
                        if (childFrame < 0) childFrame = 0;
                        if (childFrame >= childDuration) childFrame = childDuration - 1;
                    }

                    calculateBounds(element.si.symbolName, childFrame, childMatrix, recursionDepth + 1);
                }
            }
        }
    };

    for (int i = 0; i < rootDuration; ++i)
    {
        calculateBounds(spritemapData.rootSymbolName, i, AffineMatrix{}, 0);
    }

    if (!hasBounds) return;

    const float centerX = (minX + maxX) * 0.5f;
    const float centerY = (minY + maxY) * 0.5f;

    const float radians = stuff.angle * (std::acos(-1.0f) / 180.0f);
    const float c = std::cos(radians);
    const float s = std::sin(radians);

    AffineMatrix root;

    root.a = c * stuff.scaleX;
    root.b = s * stuff.scaleX;
    root.c = -s * stuff.scaleY;
    root.d = c * stuff.scaleY;

    root.tx = stuff.x + (centerX - minX) - root.a * centerX - root.c * centerY;
    root.ty = stuff.y + (centerY - minY) - root.b * centerX - root.d * centerY;

    renderSymbol(spritemapData.rootSymbolName, frame, root, 0);
}

void SDL3Sprite::renderSymbol(const std::string& symbolName, int frame, const AffineMatrix& parentMatrix, int recursionDepth)
{
    if (recursionDepth >= 32) return;

    auto symbolIt = spritemapData.symbols.find(symbolName);
    if (symbolIt == spritemapData.symbols.end()) return;

    const SpritemapSymbol& symbol = symbolIt -> second;

    for (int layerIndex = static_cast<int>(symbol.layers.size()) - 1; layerIndex >= 0; --layerIndex)
    {
        const SpritemapKeyframe* keyframe = symbol.getKeyframe(layerIndex, frame);
        if (!keyframe) continue;

        for (const SpritemapElement& element : keyframe -> elements)
        {
            if (element.isAtlasSprite)
            {
                const AffineMatrix matrix = composeMatrix(parentMatrix, element.asi.mx);
                renderPiece(element.asi.pieceName, matrix);
            }
            else
            {
                auto childIt = spritemapData.symbols.find(element.si.symbolName);
                if (childIt == spritemapData.symbols.end()) continue;

                const SpritemapSymbol& child = childIt -> second;
                const int childDuration = child.duration();
                if (childDuration <= 0) continue;

                AffineMatrix childMatrix = composeMatrix(parentMatrix, element.si.mx);

                int childFrame = element.si.firstFrame + (frame - keyframe -> index);

                const std::string& loopType = element.si.loopType;
                const bool loops = loopType == "LOOP" || loopType == "loop" || loopType == "1";

                if (loops)
                {
                    childFrame %= childDuration;
                    if (childFrame < 0) childFrame += childDuration;
                }
                else
                {
                    if (childFrame < 0) childFrame = 0;
                    if (childFrame >= childDuration) childFrame = childDuration - 1;
                }

                renderSymbol(element.si.symbolName, childFrame, childMatrix, recursionDepth + 1);
            }
        }
    }
}

void SDL3Sprite::renderPiece(const std::string& pieceName, const AffineMatrix& matrix)
{
    if (!texture) return;

    auto pieceIt = spritemapData.atlas.find(pieceName);
    if (pieceIt == spritemapData.atlas.end()) return;

    const SpritemapPiece& piece = pieceIt -> second;

    float texWidth, texHeight = 0.0f;
    SDL_GetTextureSize(texture, &texWidth, &texHeight);

    if (texWidth <= 0.0f || texHeight <= 0.0f || piece.w <= 0 || piece.h <= 0) return;

    const float width = static_cast<float>(piece.rotated ? piece.h : piece.w);
    const float height = static_cast<float>(piece.rotated ? piece.w : piece.h);

    SDL_FPoint positions[4] = {
        {matrix.a * 0.0f + matrix.c * 0.0f + matrix.tx, matrix.b * 0.0f + matrix.d * 0.0f + matrix.ty},
        {matrix.a * width + matrix.c * 0.0f + matrix.tx, matrix.b * width + matrix.d * 0.0f + matrix.ty},
        {matrix.a * width + matrix.c * height + matrix.tx, matrix.b * width + matrix.d * height + matrix.ty},
        {matrix.a * 0.0f + matrix.c * height + matrix.tx, matrix.b * 0.0f + matrix.d * height + matrix.ty}
    };

    float left = static_cast<float>(piece.x) / texWidth;
    float right = static_cast<float>(piece.x + piece.w) / texWidth;
    float top = static_cast<float>(piece.y) / texHeight;
    float bottom = static_cast<float>(piece.y + piece.h) / texHeight;

    SDL_FPoint uv[4];

    if (piece.rotated)
    {
        uv[0] = {right, top};
        uv[1] = {right, bottom};
        uv[2] = {left, bottom};
        uv[3] = {left, top};
    }
    else
    {
        uv[0] = {left, top};
        uv[1] = {right, top};
        uv[2] = {right, bottom};
        uv[3] = {left, bottom};
    }

    SDL_Vertex vertices[4];

    for (int i = 0; i < 4; ++i)
    {
        vertices[i].position = positions[i];
        vertices[i].tex_coord = uv[i];

        vertices[i].color = {stuff.color.r, stuff.color.g, stuff.color.b, stuff.alpha};
    }

    const int indices[6] = {0, 1, 2, 2, 3, 0};

    SDL_RenderGeometry(static_cast<SDL_Renderer*>(globalWindow->getRenderer()), texture, vertices, 4, indices, 6);
}

SDL3Sprite::~SDL3Sprite()
{
	SDL_DestroyTexture(texture);
}