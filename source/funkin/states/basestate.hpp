class BaseState 
{
  public:
    bool isInitialized = false;
    virtual void create() = 0;
    virtual void update(float elapsed) = 0;
    virtual void destroy() = 0;
    virtual ~BaseState();
};

class StateManager 
{
  private:
    static BaseState *curState;

  public:
    static BaseState *prevState;
    static void changeState(BaseState *state);
    static void update(float elapsed);
    static void destroy();
};