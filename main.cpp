#include <iostream>

#pragma once

#include <cmath>

#include "hlgui/Control.h"
#include "raylib.h"
#include "hlgui/Button.h"
#include "hlgui/FpsWidget.h"
#include "hlgui/TextLabel.h"
#include "hlgui/WindowControl.h"
#include "hlgui/hlgui.h"

bool _useShader = true;

void toggle_shader(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_DOWN) return;
    _useShader = !_useShader;
}

void toggle_fullscreen(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_DOWN) return;
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
        ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    } else {
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    }
    LOG("Toggled borderless window");
}

int main() {
    int renderWidth = 800;
    int renderHeight = 600;
    InitWindow(renderWidth, renderHeight, "Hyperlink Demo");
    SetTargetFPS(1200);
    RenderTexture2D gui_render_texture = LoadRenderTexture(renderWidth, renderHeight);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    GuiSetGlobalFont(LoadFont("resources/gui/fonts/JetBrainsMono-Regular.ttf"));
    GuiSetDefaultStyle(STYLE_HICONTRAST);

    Shader bloom_shader = LoadShader(0, "resources/shaders/bloom.fs");

    int shaderFrameBufferVar = GetShaderLocation(bloom_shader, "size");
    int shaderSamplesVar = GetShaderLocation(bloom_shader, "samples");
    int shaderQualityVar = GetShaderLocation(bloom_shader, "quality");
    float shaderSamples[1] = {7.5f};
    float shaderQuality[1] = {2.5f};
    SetShaderValue(bloom_shader, shaderSamplesVar,  shaderSamples, SHADER_UNIFORM_FLOAT);
    SetShaderValue(bloom_shader, shaderQualityVar, shaderQuality, SHADER_UNIFORM_FLOAT);

    Control gui_root(800, 600, ANCHOR_CENTER);
    TextLabel tl = TextLabel("topleft", ANCHOR_TOP_LEFT);
    TextLabel t = TextLabel( "top", ANCHOR_TOP);
    TextLabel tr = TextLabel("topright", ANCHOR_TOP_RIGHT);
    TextLabel l = TextLabel("left", ANCHOR_LEFT);
    TextLabel c = TextLabel("center: drag me!", ANCHOR_CENTER);
        c.EnableDragging(Rectangle(0,0,200,64))->SetWidth(200)->SetHeight(64);
    Control r = Control(100, 100, ANCHOR_RIGHT);
        Button r_child1 = Button("borderless", toggle_fullscreen, ANCHOR_CENTER);
        r.Add(&r_child1);
    Control bl = Control(40, 40, ANCHOR_BOTTOM_LEFT);
    Control b = Control(40, 40, ANCHOR_BOTTOM);
    Control br = Control(40, 40, ANCHOR_BOTTOM_RIGHT);

    WindowControl window_test = WindowControl(200,232,ANCHOR_CENTER);
    Button bloom_toggle = Button("toggle bloom", toggle_shader, ANCHOR_CENTER);
    FpsWidget fpsMonitor = FpsWidget(ANCHOR_TOP_RIGHT);
    window_test.SetTitle("Performance")->Add(&bloom_toggle)->Add(&fpsMonitor);
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
        ->Add(window_test.SetStyle(STYLE_HICONTRAST));

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            renderWidth = GetRenderWidth();
            renderHeight = GetRenderHeight();
            UnloadRenderTexture(gui_render_texture);
            gui_render_texture = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
            float fbufferSize[2] = {(float)GetRenderWidth()*1.5f, (float) GetRenderHeight()*1.5f};
            SetShaderValue(bloom_shader, shaderFrameBufferVar, fbufferSize, SHADER_UNIFORM_VEC2);
        }
        gui_root.CheckMouse(GetMousePosition());
        gui_root.BaseUpdate(GetFrameTime());
        BeginTextureMode(gui_render_texture);
        ClearBackground(TRANSPARENT);
        gui_root.BaseDraw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BG_DARK);
        if (_useShader) BeginShaderMode(bloom_shader);
        DrawTextureRec(gui_render_texture.texture,
            Rectangle( 0, 0, (float)gui_render_texture.texture.width, -(float)gui_render_texture.texture.height),
            Vector2(0,0),
            WHITE);
        if (_useShader) EndShaderMode();
        EndDrawing();
    }
    CloseWindow();
    std::cout << "Bye!" << std::endl;
    return 0;
}
