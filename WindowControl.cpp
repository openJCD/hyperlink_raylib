//
// Created by openjcd on 29/11/2024.
//

#include "WindowControl.h"

#include "TextLabel.h"

using namespace HlGui;

void WindowControl::Close() {
    delete this;
}

void WindowControl::Draw() {
    Control::Draw();
    Vector2 textSize = MeasureTextEx(m_titleFont, m_title.c_str(), 16, 1);
    int textx = m_Bounds.x + (m_Bounds.width/2 - textSize.x / 2);
    int texty = m_Bounds.y + (textSize.y / 2);
    DrawTextEx(m_titleFont, m_title.c_str(), Vector2(textx, texty), 16, 1, m_StyleProperties.foreground_color);
}

WindowControl::WindowControl(short width, short height, hl_AnchorType startAnchor) : Control(width, height,
    startAnchor) {
    m_title = string("Window");
    m_DragZone = Rectangle(0, 0, width, 20);
    m_StyleProperties = STYLE_HICONTRAST_BG;
}

Control * WindowControl::Add(Control *child) {
    auto _default = Control::Add(child);
    child->SetPaddingY(child->GetStyleProperties().padding.y + m_DragZone.height);
    return _default;
}

WindowControl *WindowControl::SetTitle(const char *title) {
    m_title = title;
    return this;
}

WindowControl::~WindowControl() = default;
