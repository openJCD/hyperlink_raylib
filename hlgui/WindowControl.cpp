//
// Created by openjcd on 29/11/2024.
//

#include "WindowControl.h"
#include "TextLabel.h"

WindowControl::WindowControl(const char* title, short width, short height) : Control(width, height) {
    m_title = title;
    m_titleLabel.SetText(title)->SetPadding(0,0)->SetBorderColor(FG_HIGHLIGHT)->SetWidth(m_Bounds.width)->SetMargin(0,5)->FillParentWidth();
    Control::Add(std::make_shared<TextLabel>(m_titleLabel));
    m_DragZone = Rectangle(0, 0, width, m_titleLabel.GetBounds().height);
}

WindowControl *WindowControl::SetTitle(const char *title) {
    m_title = title;
    m_titleLabel.SetText(title);
    return this;
}

WindowControl::~WindowControl() = default;
