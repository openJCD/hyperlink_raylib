//
// Created by openjcd on 04/12/2024.
//

#ifndef GAMENODEMAP_H
#define GAMENODEMAP_H

#include <memory>
#include "NetworkNode.h"
#include "raylib.h"

using std::shared_ptr;

class GameNodeMap {
    shared_ptr<NetworkNode> m_RegionNodes[233];
    Camera3D m_Camera = Camera3D();
public:
    GameNodeMap();
    void Render();
    void UpdateMouse();
};

#endif //GAMENODEMAP_H
