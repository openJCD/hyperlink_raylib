#include <cmath>
#include <iostream>
#include <thread>

#include "src/hlgui/Control.h"
#include "raylib.h"
#include "rlgl.h"
#include "cmake-build-release/_deps/raylib-src/src/rcamera.h"
#include "src/program.h"
#include "src/hlgame/GameNodeMap.h"
#include "src/hlgame/os/CcOS.h"
#include "src/hlgui/Button.h"
#include "src/hlgui/FpsWidget.h"
#include "src/hlgui/TextLabel.h"
#include "src/hlgui/WindowControl.h"
#include "src/hlgui/hlgui.h"
// #include "hlgui/perf_profile_helpers.h"
bool _useShader = true;

static hl_StyleProperties mainStyle = hl_StyleProperties {0,
    2,
    WHITE,
    BG_DARK_BLUE,
    DARKBLUE,
    {10,10},
    {10,10,},
    16,
    };
static hl_StyleProperties btnStyle = hl_StyleProperties {0,
    2,
    WHITE,
    DARKBLUE,
    SKYBLUE,
    {10,10},
    {10,10},
    16
};

void toggle_fullscreen(hl_ClickEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) return;
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
        ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    } else {
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    }
    GUI_LOG("Toggled borderless window");
}


int main() {
    // init //
    HlInit();

    int renderWidth = 800;
    int renderHeight = 600;
    InitWindow(renderWidth, renderHeight, "Hyperlink Demo");
    Model m_pcModel = LoadModel("resources/models/pc.obj");
    ResourceManager::AddModel("pc", m_pcModel);
    GameNodeMap map = GameNodeMap();
    SetTargetFPS(1200);
    RenderTexture2D gui_render_texture;
    RenderTexture2D game_render_texture = LoadRenderTexture(renderWidth, renderHeight);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Camera3D camera = Camera3D();
    camera.position = Vector3(15.0f, 11.0f, 15.0f);
    camera.target = Vector3(0, 0, 0);
    camera.up = Vector3(0, 1, 0);
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    GuiSetGlobalFont         (LoadFontEx("resources/gui/fonts/JetBrainsMono-Regular.ttf", 32, NULL, NULL));
    GuiSetDefaultStyle       (mainStyle);
    GuiSetButtonStyle        (btnStyle);

    CcOS ccos = CcOS(renderWidth, renderHeight);

    shared_ptr<Control> gui_root = ccos.GetRootGuiControl();

    int timer = 0;
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            renderWidth = GetRenderWidth();
            renderHeight = GetRenderHeight();
            float fbufferSize[2] = {(float)GetRenderWidth()*1.5f, (float) GetRenderHeight()*1.5f};
            game_render_texture = LoadRenderTexture(renderWidth, renderHeight);
        }
        timer += GetFrameTime();
        if (!gui_root->CheckMouse(GetMousePosition())) {
            map.UpdateMouse();
        }
        UpdateCamera(&camera, CAMERA_ORBITAL);
        ccos.Update();
        gui_root->BaseUpdate(GetFrameTime());
        gui_render_texture = gui_root->BaseDraw();

        BeginTextureMode(game_render_texture);
        ClearBackground(TRANSPARENT);
        BeginMode3D(camera);
        DrawSphere({0,0,0},6, RED);
        EndMode3D();
        EndTextureMode();

        // multithreaded calls //
        // std::thread threadUpdate(HlUpdate);
        // std::thread threadDraw(HlDraw);
        // threadUpdate.join();
        // threadDraw.join();
        // ------------------- //
        BeginDrawing();
        ClearBackground(TRANSPARENT);

        DrawTextureRec(game_render_texture.texture,
            Rectangle( 0, 0, (float)game_render_texture.texture.width, -(float)game_render_texture.texture.height),
            Vector2(0,0),
            WHITE);
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
