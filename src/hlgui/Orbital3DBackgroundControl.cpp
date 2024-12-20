//
// Created by openjcd on 20/12/2024.
//

#include "Orbital3DBackgroundControl.h"

void Orbital3DBackgroundControl::Draw() {
    //
    // Control::Draw();
    UpdateCamera(&m_camera, CAMERA_ORBITAL);
    BeginMode3D(m_camera);
        // DrawCubeWires({0,0,0}, 5, 12, 11, m_StyleProperties.foreground_color);
        // DrawPoly({0,0}, 3, 5, 180, m_StyleProperties.foreground_color);
        DrawModelWires(*m_model, {-2.5,0,0}, 2.0f, m_StyleProperties.foreground_color);
    EndMode3D();
}
void Orbital3DBackgroundControl::PostDraw() {

}

void Orbital3DBackgroundControl::Update(float Gametime) {
    Control::Update(Gametime);
    Redraw=true; //constant redraw so orbit effect works properly
}