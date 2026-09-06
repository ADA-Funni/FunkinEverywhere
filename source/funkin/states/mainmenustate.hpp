#include "basestate.hpp"

class MainMenuState : public BaseState 
{
  public:
    void create() override;
    void update(float elapsed) override;
    void destroy() override;

    MainMenuState();
    ~MainMenuState();
};