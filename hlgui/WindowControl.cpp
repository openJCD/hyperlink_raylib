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
}

WindowControl::WindowControl(short width, short height, hl_AnchorType startAnchor) : Control(width, height,
    startAnchor) {
    m_title = string("Window");
    Control::Add(m_titleLabel.SetPadding(0,0)->SetWidth(m_Bounds.width)->SetMargin(0,0));
    m_DragZone = Rectangle(0, 0, width, m_titleLabel.GetBounds().height);
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
