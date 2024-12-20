//
// Created by openjcd on 29/11/2024.
//

#include "WindowControl.h"
#include "TextLabel.h"
#include "gui_structs.h"
#include "hlgui.h"

WindowControl::WindowControl(const char* title, short width, short height) : Control(width, height) {
    m_title = title;
    IsFloating = true;
    CREATE_BUTTON_MEMBER_CALLBACK(_close, f_close);
    hl_StyleProperties btn_close_style = ResourceManager::GetStyle("textLabel");
    btn_close_style.padding = {2,0};
    hl_StyleProperties btn_close_hover_style = ResourceManager::GetStyle("button");
    btn_close_hover_style.padding = {2,0};
    m_titleBar->SetText(title)->FillParentWidth()->SetPadding(0,0)->SetMargin(5,10);
    m_titleBar->Add(m_closeButton);
    Add(m_titleBar);
    m_closeButton->SetClickedStyle(btn_close_style)->SetStyle(btn_close_style)
        ->SetHoveredStyle(btn_close_hover_style)
        ->SetAnchor(ANCHOR_RIGHT)
        ->Deactivate()
        ->SetClickAction(f_close);
    //m_closeButton.Disable();
    m_DragZone = Rectangle(0, 0, width, m_titleBar->GetBounds().height);
}

void WindowControl::_close(hl_ClickEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) return;
    Disable();
    if (_closeCallback != nullptr) {
        _closeCallback();
    }
}

void WindowControl::PostDraw() {
    Control::PostDraw();
}
WindowControl *WindowControl::SetTitle(const char *title) {
    m_titleBar->SetText(title);
    m_title = title;
    return this;
}

WindowControl * WindowControl::EnableCloseButton() {

    m_closeButton->Activate();
    return this;
}

WindowControl* WindowControl::OnClose(std::function<void()> callback) {
    _closeCallback = callback;
    return this;
}

WindowControl::~WindowControl() = default;