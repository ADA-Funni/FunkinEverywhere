#include "basestate.hpp"

class TitleState : public BaseState 
{
  public:
    void create() override;
    void update(float elapsed) override;
    void destroy() override;

    TitleState();
    ~TitleState();
};