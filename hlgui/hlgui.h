//
// Created by openjcd on 01/12/2024.
//

#ifndef HLGUI_H
#define HLGUI_H
#include <stack>

#include "Control.h"
#include "ResourceManager.h"

// gui styling methods
static void GuiSetGlobalFont(Font font) {
    ResourceManager::AddFont("default", font);
}

#endif //HLGUI_H
