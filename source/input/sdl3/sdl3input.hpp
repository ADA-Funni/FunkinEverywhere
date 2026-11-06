#pragma once

#include "sdl3inputhandler.hpp"

extern SDL3KeyboardHandler keyboardHandler;
extern SDL3ControllerHandler controllerHandler;
extern SDL3TouchHandler touchHandler;

void initInput();