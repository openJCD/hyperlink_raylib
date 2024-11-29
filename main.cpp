#include <iostream>

#include "Control.h"
#include "raylib.h"
#include "TextLabel.h"

using namespace HlGui;

void print_status_msg(hl_ClickEventArgs args) {
    cout << args.sender->GetDebugString() + string(" was clicked") << endl;
}

int main() {
    InitWindow(800, 600, "Hyperlink Demo");
    SetTargetFPS(1000);

    Font fnt_main = LoadFontEx("resources/gui/fonts/JetBrainsMono-Regular.ttf", 24, NULL, NULL);
    Control gui_root(799, 599, ANCHOR_TOP_LEFT);
    TextLabel tl = TextLabel(fnt_main, "topleft", ANCHOR_TOP_LEFT);
        tl.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel t = TextLabel(fnt_main, "top", ANCHOR_TOP);
        t.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel tr = TextLabel(fnt_main, "topright", ANCHOR_TOP_RIGHT);
        tr.SetStyle(STYLE_BUTTON_STATIC);
    TextLabel l = TextLabel(fnt_main, "left", ANCHOR_LEFT);
    TextLabel c = TextLabel(fnt_main, "center: drag me!", ANCHOR_CENTER);
        c.EnableDragging(Rectangle(0,0,200,64))->SetWidth(200)->SetHeight(64);
    Control r = Control(100, 100, ANCHOR_RIGHT);
        TextLabel r_child1 = TextLabel(fnt_main,"hi",ANCHOR_CENTER);
        r_child1.SetStyle(STYLE_HICONTRAST_BG)->SetClickAction(print_status_msg);
;
        r.Add(&r_child1)->SetStyle(STYLE_HICONTRAST_BG);
    Control bl = Control(40, 40, ANCHOR_BOTTOM_LEFT);
    Control b = Control(40, 40, ANCHOR_BOTTOM);
    Control br = Control(40, 40, ANCHOR_BOTTOM_RIGHT);
    gui_root.Add(&tl)->Add(&t)->Add(&tr)->Add(&l)->Add(&c)->Add(&r)->Add(&bl)->Add(&b)->Add(&br)->SetColor(RAYWHITE);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(650, 10);
        // draw the rest of the stuff
        gui_root.BaseUpdate(GetFrameTime());
;       gui_root.BaseDraw();
        EndDrawing();
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
