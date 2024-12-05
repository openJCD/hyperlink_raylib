//
// Created by openjcd on 04/12/2024.
//

#include "GameNodeMap.h"

#include <cmath>
#include <math.h>

#include "raylib.h"
void GameNodeMap::UpdateMouse() {
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        m_Camera.position.x += cos(GetMouseDelta().x * PI / 180);
        m_Camera.position.z += sin(GetMouseDelta().x * PI / 180);
    }
}

GameNodeMap::GameNodeMap() {
    m_Camera = Camera3D();
    m_Camera.position = Vector3(15.0f, 5.0f, 15.0f);
    m_Camera.target = Vector3(0, 0, 0);
    m_Camera.up = Vector3(0, 1, 0);
    m_Camera.projection = CAMERA_ORBITAL;
}

void GameNodeMap::Render() {
    BeginMode3D(m_Camera);
    DrawSphereWires((Vector3){0,0, 0}, 10.0f, 20, 20, RED);
    EndMode3D();
}
