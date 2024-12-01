#include <iostream>

#pragma once

#include "hlgui/Control.h"
#include "raylib.h"
#include "hlgui/Button.h"
#include "hlgui/TextLabel.h"
#include "hlgui/WindowControl.h"
#include "hlgui/hlgui.h"

void toggle_window_resize(hl_ButtonEventArgs args) {
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
    SetTargetFPS(360);
    RenderTexture2D gui_render_texture = LoadRenderTexture(800, 600);


    GuiSetGlobalFont(LoadFontEx("resources/gui/fonts/JetBrainsMono-Regular.ttf", 32, NULL, NULL));
    Control gui_root(800, 600, ANCHOR_CENTER);
    TextLabel tl = TextLabel( "topleft", ANCHOR_TOP_LEFT);
        tl.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel t = TextLabel( "top", ANCHOR_TOP);
        t.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel tr = TextLabel("topright", ANCHOR_TOP_RIGHT);
        tr.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel l = TextLabel("left", ANCHOR_LEFT);
    TextLabel c = TextLabel("center: drag me!", ANCHOR_CENTER);
        c.EnableDragging(Rectangle(0,0,200,64))->SetWidth(200)->SetHeight(64);
    Control r = Control(100, 100, ANCHOR_RIGHT);
        Button r_child1 = Button("hi", toggle_window_resize, ANCHOR_CENTER);
        r_child1.SetHoveredStyle(STYLE_BUTTON_HOVERED)->SetStyle(STYLE_BUTTON_STATIC);
        r.Add(&r_child1)->SetStyle(STYLE_HICONTRAST_BG);
    Control bl = Control(40, 40, ANCHOR_BOTTOM_LEFT);
    Control b = Control(40, 40, ANCHOR_BOTTOM);
    Control br = Control(40, 40, ANCHOR_BOTTOM_RIGHT);

    WindowControl window_test = WindowControl(100,132,ANCHOR_CENTER);

    gui_root
        .Add(&tl)
        ->Add(&t)
        ->Add(&tr)
        ->Add(&l)
        ->Add(&c)
        ->Add(&r)
        ->Add(&bl)
        ->Add(&b)
        ->Add(&br)
        ->SetColor(RAYWHITE)
        ->Add(&window_test);

    while (!WindowShouldClose()) {
        if (IsWindowResized())
            gui_render_texture = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());

        gui_root.CheckMouse(GetMousePosition());
        gui_root.BaseUpdate(GetFrameTime());

        BeginTextureMode(gui_render_texture);
        ClearBackground(RAYWHITE);
        gui_root.BaseDraw();
        EndTextureMode();

        BeginDrawing();
        DrawTextureRec(gui_render_texture.texture,
            Rectangle( 0, 0, (float)gui_render_texture.texture.width, -(float)gui_render_texture.texture.height),
            Vector2(0,0),
            WHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    std::cout << "Bye!" << std::endl;
    return 0;
}
