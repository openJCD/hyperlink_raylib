//
// Created by openjcd on 01/12/2024.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "Control.h"
#include "TextLabel.h"
class Button : public TextLabel {
protected:
    hl_StyleProperties m_StyleProperties_Default;
    hl_StyleProperties m_StyleProperties_Hovered;
    hl_StyleProperties m_StyleProperties_Clicked;

    bool _wasHovered = false;
    bool _wasClicked = false;
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();
    void Update(float gameTime) override;
public:
    Button(const char* text, std::function<void(hl_ButtonEventArgs)>& onclick);
    ~Button() override = default;
    Button* SetHoveredStyle(hl_StyleProperties style);
    Button* SetClickedStyle(hl_StyleProperties style);
    Button* SetStyle(hl_StyleProperties style) override;
};

#endif //BUTTON_H
