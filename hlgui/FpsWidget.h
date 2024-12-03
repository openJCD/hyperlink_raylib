//
// Created by openjcd on 03/12/2024.
//

#pragma once
#include "Control.h"
#ifndef FPSWIDGET_H
#define FPSWIDGET_H

class FpsWidget  : public Control {
protected:
    void Draw() override {
        Control::Draw();
        DrawFPS((int)m_Bounds.x, (int)(m_Bounds.y));
    };
    void Update(float gameTime) override {
    }
public:
    FpsWidget(short w, short h, hl_AnchorType anchor)
        : Control(w, h, anchor) {
    }

    explicit FpsWidget(hl_AnchorType anchor)
        : Control(anchor) {
        m_Bounds.width = MeasureText("FPS 1000", 20);
        m_Bounds.height = 20;
    }
};


#endif //FPSWIDGET_H
