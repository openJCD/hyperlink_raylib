//
// Created by openjcd on 01/12/2024.
//
#pragma once
#ifndef HLGUI_H
#define HLGUI_H
#include <memory>
#include <stack>

#include "Control.h"
#include "WindowControl.h"
#include "ResourceManager.h"
#include "TextLabel.h"
#include "GuiScene.h"
#include "gui_structs.h"

#define CREATE_BUTTON_MEMBER_CALLBACK(member_name, var_name) std::function<void(hl_ButtonEventArgs)> var_name = std::bind(member_name, this, std::placeholders::_1);

using std::stack, std::list, std::make_shared, std::to_string; // gui styling methods
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
