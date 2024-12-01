//
// Created by openjcd on 01/12/2024.
//

#include "Button.h"

#include <iostream>
#include "structs.cpp"
#include <ostream>

void Button::OnMouseEnter() {  }
void Button::OnMouseLeave() {  }

void Button::Update(float gameTime) {
    TextLabel::Update(gameTime);
    if (IsHovered && !_wasHovered) {
        m_StyleProperties = m_StyleProperties_Hovered;
        RecalculateBounds();
    } else if (!IsHovered && _wasHovered) {
        m_StyleProperties = m_StyleProperties_Default;
        RecalculateBounds();
    }
    if (IsClicked && !_wasClicked) {
        m_StyleProperties = m_StyleProperties_Clicked;
        RecalculateBounds();
    } else if (!IsClicked and _wasClicked) {
        m_StyleProperties = m_StyleProperties_Hovered;
        RecalculateBounds();
    }
    _wasClicked = IsClicked;
    _wasHovered = IsHovered;
}

Button::Button(const char *text, void (*onclick)(hl_ButtonEventArgs), hl_AnchorType anchor): TextLabel(text, anchor) {
    SetStyle(m_StyleProperties_Hovered);
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
