//
// Created by openjcd on 27/11/2024.
//
#include <raylib.h>
#include "ResourceManager.h"
#define TRANSPARENT Color(0, 0, 0, 0)
#define STYLE_DEFAULT hl_StyleProperties()
#define STYLE_BUTTON_STATIC hl_StyleProperties {.rounding = 0, .border_thickness = 1,  .foreground_color = RAYWHITE, .background_color = DARKGRAY, .border_color = GRAY, .margin = {10,10}}
#define STYLE_TEXT_LABEL hl_StyleProperties {.rounding = 0, .border_thickness = 0, .foreground_color = BLACK, .background_color = TRANSPARENT, .margin={3,3}}
#define STYLE_HICONTRAST_BG hl_StyleProperties {.background_color = YELLOW}
#define LOG(msg) std::cout << "[GUI INFO]: " << msg <<  std::endl

namespace HlGui {
    class Control;
    class TextLabel;
}
using namespace HlGui;
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
    Color background_color = Color(0, 0, 0, 0);
    Color border_color = GRAY;
    Vector2 padding = {10,10};
    Vector2 margin = {10,10};
    short font_size = 24;
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
