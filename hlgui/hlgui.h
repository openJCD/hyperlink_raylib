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
static void GuiSetDefaultStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("default", style);
}
static void GuiSetButtonStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("button", style);
}
static void GuiSetButtonHoveredStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("buttonHovered", style);
}
static void GuiSetWindowStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("window", style);
}
static void GuiSetTextLabelStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("textLabel", style);
}
#endif //HLGUI_H
