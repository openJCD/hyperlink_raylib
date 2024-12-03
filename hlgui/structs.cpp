﻿//
// Created by openjcd on 27/11/2024.
//
#pragma once
#include <raylib.h>

#define TRANSPARENT Color(0, 0, 0, 0)
#define BG_DARK Color (23, 19, 19, 225)
#define FG_HIGHLIGHT Color(255, 173, 51, 255)

#define STYLE_DEFAULT hl_StyleProperties()
#define STYLE_BUTTON_STATIC hl_StyleProperties {.rounding = 0, .border_thickness = 1,  .foreground_color = RAYWHITE, .background_color = DARKGRAY, .border_color = GRAY, .margin = {10,10}}
#define STYLE_BUTTON_HOVERED hl_StyleProperties {.rounding = 0, .border_thickness=2, .foreground_color = BG_DARK, .background_color=FG_HIGHLIGHT, .border_color=BG_DARK}
#define STYLE_TEXT_LABEL hl_StyleProperties {.rounding = 0, .border_thickness = 0, .foreground_color = BLACK, .background_color = TRANSPARENT, .margin={3,3}}
#define STYLE_HICONTRAST hl_StyleProperties { .foreground_color = FG_HIGHLIGHT, .background_color = BG_DARK, .border_color=FG_HIGHLIGHT }


#define LOG(msg) std::cout << "[GUI INFO]: " << msg << std::endl
class Control;
using namespace std;
enum hl_AnchorType {
    ANCHOR_LEFT,
    ANCHOR_RIGHT,
    ANCHOR_TOP,
    ANCHOR_BOTTOM,
    ANCHOR_CENTER,
    ANCHOR_TOP_LEFT,
    ANCHOR_TOP_RIGHT,
    ANCHOR_BOTTOM_LEFT,
    ANCHOR_BOTTOM_RIGHT,
    ANCHOR_AUTO
};

enum hl_GuiLayoutType {
    GUI_LAYOUT_VERTICAL,
    GUI_LAYOUT_HORIZONTAL
};

struct hl_StyleProperties {
    float rounding = 0;
    __int8 border_thickness = 1;
    Color foreground_color = Color(255, 70, 70, 255);
    Color background_color = RAYWHITE;
    Color border_color = GRAY;
    Vector2 padding = {10,10};
    Vector2 margin = {10,10};
    short font_size = 16;
    bool fill_parent_h = false;
    bool fill_parent_w = false;
};

enum MouseMask {
    MOUSE_MASK_UP,
    MOUSE_MASK_DOWN,
};

struct hl_ButtonEventArgs {
    MouseMask mask;
    MouseButton button;
    Control* sender;
};

enum hl_BindType {
    DATABIND_NONE,
    DATABIND_INTEGER,
    DATABIND_FLOAT,
    DATABIND_STRING,
};

struct hl_DataBind {
    hl_BindType type = DATABIND_NONE;
    void* p_Data = nullptr;
    int location_index = -1;
};
