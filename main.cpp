#include <iostream>
#include "hlgui/Control.h"
#include "raylib.h"
#include "rlgl.h"
#include "hlgame/GameNodeMap.h"
#include "hlgame/os/CcOS.h"
#include "hlgui/Button.h"
#include "hlgui/FpsWidget.h"
#include "hlgui/TextLabel.h"
#include "hlgui/WindowControl.h"
#include "hlgui/hlgui.h"
// #include "hlgui/perf_profile_helpers.h"
bool _useShader = true;

void toggle_fullscreen(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) return;
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
        ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    } else {
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    }
    GUI_LOG("Toggled borderless window");
}


int main() {
    int renderWidth = 800;
    int renderHeight = 600;
    InitWindow(renderWidth, renderHeight, "Hyperlink Demo");
    GameNodeMap map = GameNodeMap();
    // SetTargetFPS(1200);
    RenderTexture2D gui_render_texture = LoadRenderTexture(renderWidth, renderHeight);
    RenderTexture2D game_render_texture = LoadRenderTexture(renderWidth, renderHeight);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    GuiSetGlobalFont(LoadFontEx("resources/gui/fonts/JetBrainsMono-Regular.ttf", 40, NULL, NULL));
    GuiSetDefaultStyle(STYLE_HICONTRAST);
    GuiSetButtonStyle(STYLE_BUTTON_STATIC);
    GuiSetTextLabelStyle(STYLE_TEXT_LABEL);

    CcOS ccos = CcOS(renderWidth, renderHeight);
    shared_ptr<Control> gui_root = ccos.GetRootGuiControl();
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            renderWidth = GetRenderWidth();
            renderHeight = GetRenderHeight();
            UnloadRenderTexture(gui_render_texture);
            gui_render_texture = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
            float fbufferSize[2] = {(float)GetRenderWidth()*1.5f, (float) GetRenderHeight()*1.5f};
        }

        if (!gui_root->CheckMouse(GetMousePosition())) {
            map.UpdateMouse();
        }
        ccos.Update();
        gui_root->BaseUpdate(GetFrameTime());
        gui_render_texture = gui_root->BaseDraw();

        BeginDrawing();
        ClearBackground(BG_DARK);
        //map.Render();
        DrawTextureRec(gui_render_texture.texture,
            Rectangle( 0, 0, (float)gui_render_texture.texture.width, -(float)gui_render_texture.texture.height),
            Vector2(0,0),
            WHITE);
        DrawFPS(10,10);
        EndDrawing();
    }
    CloseWindow();
    std::cout << "Bye!" << std::endl;
    return 0;
}
