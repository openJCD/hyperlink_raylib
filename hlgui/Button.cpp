//
// Created by openjcd on 01/12/2024.
//

#include "Button.h"

#include <utility>
#include "gui_structs.h"

void Button::OnMouseEnter() {  }
void Button::OnMouseLeave() {  }

void Button::Update(float gameTime) {
    TextLabel::Update(gameTime);
    if (IsClicked and !_wasClicked and IsHovered) {
        m_StyleProperties = m_StyleProperties_Clicked;
        RecalculateBounds();
    } else if (!IsClicked and _wasClicked) {
        m_StyleProperties = m_StyleProperties_Hovered;
        RecalculateBounds();
    }
    if (IsHovered and !_wasHovered && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_StyleProperties = m_StyleProperties_Hovered;
        RecalculateBounds();
    } else if (!IsHovered and _wasHovered) {
        m_StyleProperties = m_StyleProperties_Default;
        RecalculateBounds();
    }
    _wasHovered = IsHovered;
    _wasClicked = IsClicked;
}
Button::Button(const char *text, std::function<void(hl_ButtonEventArgs)>& onclick, hl_AnchorType anchor): TextLabel(text, anchor) {
    _debug_string = "Button_'" + string(text) + "'";
    m_StyleProperties = ResourceManager::GetStyle("button");
    m_StyleProperties_Hovered = ResourceManager::GetStyle("buttonHovered");
    m_StyleProperties_Default = m_StyleProperties;
    OnClick = onclick;
}

Button * Button::SetHoveredStyle(hl_StyleProperties style) {
    m_StyleProperties_Hovered = style;
    return this;
}

Button * Button::SetClickedStyle(hl_StyleProperties style) {
    m_StyleProperties_Clicked = style;
    return this;
}
/// Set the default button style!
Button* Button::SetStyle(hl_StyleProperties style) {
    m_StyleProperties = style;
    m_StyleProperties_Default = style;
    return this;
}
