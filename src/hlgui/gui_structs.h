//
// Created by openjcd on 27/11/2024.
//
#pragma once
#include <raylib.h>

#define TRANSPARENT Color (0, 0, 0, 0)
#define BG_DARK_YELLOW Color (23, 19, 19, 225)
#define FG_HIGHLIGHT_YELLOW Color (255, 173, 51, 255)
#define BG_DARK_BLUE Color (0, 5, 40, 225)

#define STYLE_DEFAULT hl_StyleProperties()
#define STYLE_BUTTON_STATIC hl_StyleProperties {.rounding = 0, .border_thickness = 2,  .foreground_color = RAYWHITE, .background_color = DARKGRAY, .border_color = GRAY, .padding={10,10}, .margin = {10,10}}
#define STYLE_BUTTON_HOVERED hl_StyleProperties {.rounding = 0, .border_thickness=1, .foreground_color = BG_DARK_YELLOW, .background_color=FG_HIGHLIGHT_YELLOW, .border_color=BG_DARK_YELLOW, .padding={10,10}}
#define STYLE_TEXT_LABEL hl_StyleProperties {.rounding = 0, .border_thickness = 0, .foreground_color = FG_HIGHLIGHT_YELLOW, .background_color = TRANSPARENT, .margin={3,3}}
#define STYLE_HICONTRAST hl_StyleProperties { .border_thickness = 1, .foreground_color = FG_HIGHLIGHT_YELLOW, .background_color = BG_DARK_YELLOW, .border_color=FG_HIGHLIGHT_YELLOW }

#define GUI_LOG(msg) std::cout << "[GUI INFO]: " << msg << std::endl

class Control;
enum hl_AnchorType {
    ANCHOR_TOP_LEFT,
    ANCHOR_TOP,
    ANCHOR_TOP_RIGHT,
    ANCHOR_LEFT,
    ANCHOR_CENTER,
    ANCHOR_RIGHT,
    ANCHOR_BOTTOM_LEFT,
    ANCHOR_BOTTOM,
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
    Vector2 padding = {0,0};
    Vector2 margin = {10,10};
    short font_size = 16;
    bool fill_parent_h = false;
    bool fill_parent_w = false;
    float opacity = 1.0f;
};

enum MouseMask {
    MOUSE_MASK_UP,
    MOUSE_MASK_DOWN,
};

struct hl_ClickEventArgs {
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

enum hl_TextAlign {
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT,
};

struct hl_DataBind {
    hl_BindType type = DATABIND_NONE;
    void* p_Data = nullptr;
    int location_index = -1;
};

struct hl_LayoutState {
    Vector2 cursor_position;
    hl_GuiLayoutType layout_type;
};

class null_gui_exception : public std::exception {
private:
    std::string msg;
public:
    explicit null_gui_exception(const char* message) {
        msg = message;
    };
    const char* what() {
        return msg.c_str();
    }
};