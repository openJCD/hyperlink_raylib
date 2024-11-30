#include <iostream>

#pragma once

#include "Control.h"
#include "raylib.h"
#include "TextLabel.h"
#include "WindowControl.h"
using namespace HlGui;

void toggle_window_resize(hl_ClickEventArgs args) {
    if (args.mask != MOUSE_MASK_DOWN) return;
    if (IsWindowState(FLAG_WINDOW_RESIZABLE)) {
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
    } else {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }
    LOG("Toggled resizeability");
}

int main() {
    InitWindow(800, 600, "Hyperlink Demo");
    ResourceManager resx = ResourceManager();
    SetTargetFPS(240);

    resx.AddFont("main", LoadFontEx("resources/gui/fonts/JetBrainsMono-Regular.ttf", 32, NULL, NULL));
    Control gui_root(700, 500, ANCHOR_CENTER);
    TextLabel tl = TextLabel(resx.GetFont("main"), "topleft", ANCHOR_TOP_LEFT);
        tl.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel t = TextLabel(resx.GetFont("main"), "top", ANCHOR_TOP);
        t.SetStyle(STYLE_BUTTON_STATIC);
    hl_StyleProperties();
    TextLabel tr = TextLabel(resx.GetFont("main"), "topright", ANCHOR_TOP_RIGHT);
        tr.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel l = TextLabel(resx.GetFont("main"), "left", ANCHOR_LEFT);
    TextLabel c = TextLabel(resx.GetFont("main"), "center: drag me!", ANCHOR_CENTER);
        c.EnableDragging(Rectangle(0,0,200,64))->SetWidth(200)->SetHeight(64);
    Control r = Control(100, 100, ANCHOR_RIGHT);
        TextLabel r_child1 = TextLabel(resx.GetFont("main"),"hi",ANCHOR_CENTER);
        r_child1.SetStyle(STYLE_HICONTRAST_BG)->SetClickAction(toggle_window_resize);
        r.Add(&r_child1)->SetStyle(STYLE_HICONTRAST_BG);
    Control bl = Control(40, 40, ANCHOR_BOTTOM_LEFT);
    Control b = Control(40, 40, ANCHOR_BOTTOM);
    Control br = Control(40, 40, ANCHOR_BOTTOM_RIGHT);

    WindowControl window_test = WindowControl(100,132,ANCHOR_CENTER);

    gui_root.Add(&tl)->Add(&t)->Add(&tr)->Add(&l)->Add(&c)->Add(&r)->Add(&bl)->Add(&b)->Add(&br)->SetColor(RAYWHITE)->Add(&window_test);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // draw the rest of the stuff
        gui_root.BaseUpdate(GetFrameTime());
        gui_root.BaseDraw();
        DrawFPS(650, 10);
        EndDrawing();
    }
    CloseWindow();
    std::cout << "Bye!" << std::endl;
    return 0;
}
