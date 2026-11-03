#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

enum class FUNKIN_KEY_INDEX {
    L_STICK_LEFT,
    L_STICK_DOWN,
    L_STICK_UP,
    L_STICK_RIGHT,
    L_STICK_PRESSED,
    R_STICK_LEFT,
    R_STICK_DOWN,
    R_STICK_UP,
    R_STICK_RIGHT,
    R_STICK_PRESSED,
    DPAD_LEFT,
    DPAD_DOWN,
    DPAD_UP,
    DPAD_RIGHT,
    X,
    A,
    Y,
    B,
    SHOULDER_L,
    SHOULDER_R,
    LEFT_TRIGGER,
    RIGHT_TRIGGER,
    START,
    BACK,
    COUNT,
};

static constexpr const char *FUNKIN_KEY_INDEX_STRINGS[] = {
    "LeftStickLeft",
    "LeftStickDown",
    "LeftStickUp",
    "LeftStickRight",
    "LeftStickPressed",
    "RightStickLeft",
    "RightStickDown",
    "RightStickUp",
    "RightStickRight",
    "RightStickPressed",
    "dpadLeft",
    "dpadDown",
    "dpadUp",
    "dpadRight",
    "X",
    "A",
    "Y",
    "B",
    "L",
    "R",
    "LT",
    "RT",
    "start",
    "back"
};

enum class FUNKIN_ACTION
{
    NOTE_LEFT,
    NOTE_DOWN,
    NOTE_UP,
    NOTE_RIGHT,
    UI_LEFT,
    UI_DOWN,
    UI_UP,
    UI_RIGHT,
    ACCEPT,
    BACK,
    PAUSE,
    RESET,
    DEBUG_1,
    DEBUG_2,
    DEBUG_3,
    COUNT
};

static constexpr const char* FUNKIN_ACTION_STRINGS[] = {
    "note left",
    "note down",
    "note up",
    "note right",
    "left",
    "down",
    "up",
    "right",
    "accept",
    "back",
    "pause",
    "reset",
    "debug 1",
    "debug 2",
    "debug 3"
};

enum class INPUT_TYPE
{
    KEYBOARD,
    CONTROLLER_BUTTON,
    CONTROLLER_AXIS,
    TOUCH
};

struct PhysicalInput
{
    INPUT_TYPE type;

    int code;
    std::int64_t device = 0;

    bool operator == (const PhysicalInput& other) const
    {
        return type == other.type && code == other.code && device == other.device;
    }
};

struct Keybind
{
    FUNKIN_ACTION action;
    std::vector<PhysicalInput> inputs;
};

struct TouchRegion
{
    FUNKIN_ACTION action;

    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;

    bool pressed = false;
};

struct InputState
{
    bool pressed = false;
    bool justPressed = false;
    bool justReleased = false;
};

class InputManager
{
    private:
        std::vector<Keybind> keybinds;
        std::array<InputState, static_cast<int>(FUNKIN_ACTION::COUNT)> states;

        std::vector<PhysicalInput> activeInputs;
        void refreshStates();

    public:
        void init();
        void update();

        void setInput(PhysicalInput input, bool pressed);
        void releaseAll(INPUT_TYPE type);

        bool pressed(FUNKIN_ACTION action);
        bool justPressed(FUNKIN_ACTION action);
        bool justReleased(FUNKIN_ACTION action);

        void bind(FUNKIN_ACTION action, PhysicalInput input);
        void unbind(FUNKIN_ACTION action, PhysicalInput input);

        void clear();
};

extern InputManager inputManager;