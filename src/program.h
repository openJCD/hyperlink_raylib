//
// Created by openjcd on 12/12/2024.
//
#pragma once
#include "raylib.h"
#include "hlgui/gui_structs.h"

inline static int _updateTick = 0;
inline static int _drawTick = 0;

// Testing async/multithreading //

inline void HlInit() {
}

inline void HlUpdate() {
    _updateTick++;
    if (_updateTick>1000) {
        _updateTick=0;
        std::cout<<"¦UPDATE¦ Ran update async" <<std::endl;
    }
}

inline void HlDraw() {
    _drawTick++;
    if (_drawTick>1000) {
        _drawTick=0;
        std::cout<<"¦DRAW¦ Ran draw async" <<std::endl;
    }
}
