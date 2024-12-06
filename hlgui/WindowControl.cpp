//
// Created by openjcd on 29/11/2024.
//

#include "WindowControl.h"
#include "TextLabel.h"

void WindowControl::Draw() {
    Control::Draw();
}

WindowControl::WindowControl(const char* title, short width, short height, hl_AnchorType startAnchor) : Control(width, height,
    startAnchor) {
    m_title = title;
    m_titleLabel.SetPadding(0,0)->SetWidth(m_Bounds.width)->SetMargin(0,5)->FillParentWidth();
    Control::Add(std::make_shared<TextLabel>(m_titleLabel));
    m_DragZone = Rectangle(0, 0, width, m_titleLabel.GetBounds().height);
}

Control * WindowControl::Add(shared_ptr<Control> child) {
    auto _default = Control::Add(child);

    return _default;
}

WindowControl *WindowControl::SetTitle(const char *title) {
    m_title = title;
    m_titleLabel.SetText(title);
    return this;
}

WindowControl::~WindowControl() = default;
