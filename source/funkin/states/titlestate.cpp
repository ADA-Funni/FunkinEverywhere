#include "titlestate.hpp"
#include "../../assets/funkinsprite.hpp"
#include "../../assets/spritemanager.hpp"
#include "../../rendering/window.hpp"

TitleState::TitleState()
{
    create();
}

TitleState::~TitleState()
{
    destroy();
}

void TitleState::startIntro()
{
    logoBl = new FunkinSprite("ui/title/logo-bumpin", "sparrow");
    logoBl -> getParams().x = -150;
    logoBl -> getParams().y = -100;
    logoBl -> addAnim("bump", "logo bumpin", 24, true);
    sprites.add(logoBl);
    
    gfDance = new FunkinSprite("ui/title/gf-dance-title", "sparrow");
    gfDance -> getParams().x = globalWindow -> getWidth() * 0.4;
    gfDance -> getParams().y = globalWindow -> getHeight() * 0.07;
    gfDance -> addAnim("danceLeft", "gfDance", 24, true);
    gfDance -> addAnim("danceRight", "gfDance", 24, true);
    sprites.add(gfDance);
}

void TitleState::create()
{
    startIntro();
    logoBl -> playAnim("bump");
}

void TitleState::update(float elapsed)
{

}

void TitleState::destroy()
{

}