#include "basestate.hpp"
#include "../../assets/funkinsprite.hpp"

class TitleState : public BaseState 
{
  public:
    void create() override;
    void update(float elapsed) override;
    void destroy() override;

    TitleState();
    ~TitleState();

    FunkinSprite* logoBl;
    FunkinSprite* gfDance;
    
    void startIntro();
};