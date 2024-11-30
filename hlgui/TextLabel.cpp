//
// Created by openjcd on 28/11/2024.
//

#include "TextLabel.h"

namespace HlGui {
    void TextLabel::Draw() {
        Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_fntSize, 1);
        int textx = m_Bounds.x + (m_Bounds.width/2 - textSize.x / 2);
        int texty = m_Bounds.y + (m_Bounds.height/2 - textSize.y / 2);
        DrawRectangleRounded(m_Bounds, m_StyleProperties.rounding, 10, m_StyleProperties.background_color);
        if (m_StyleProperties.border_thickness>0)
            DrawRectangleRoundedLinesEx(m_Bounds, m_StyleProperties.rounding, 10, m_StyleProperties.border_thickness, m_StyleProperties.border_color);
        DrawTextEx(m_font, m_text.c_str(), Vector2(textx, texty), m_fntSize, 1, m_StyleProperties.foreground_color);
    }
    TextLabel::TextLabel(Font &font, const char* text, hl_AnchorType anchor): Control(anchor) {
        m_text = text;
        _debug_string = "TextLabel_'" + string(text) + "'";
        m_StyleProperties = STYLE_DEFAULT;
        m_Bounds = Rectangle(0,0,(MeasureTextEx(m_font, text, m_fntSize, 1).x+m_StyleProperties.margin.x*2), m_fntSize+m_StyleProperties.margin.y*2);
        m_font = font;
    }
    TextLabel::TextLabel(const char* text, hl_AnchorType anchor): Control(anchor) {
        m_text = text;
        _debug_string = "TextLabel_'" + string(text) + "'";
        m_StyleProperties = STYLE_DEFAULT;
        m_Bounds = Rectangle(0, 0, MeasureText(text, m_fntSize) + m_StyleProperties.margin.x * 2,
                             m_fntSize + m_StyleProperties.margin.y * 2);
        m_font = GetFontDefault();
    }
    TextLabel::~TextLabel() {
        m_text.clear();
    }
    void TextLabel::Update(float gameTime) {
        this->Control::Update(gameTime);
    }

    TextLabel * TextLabel::SetText(const char *text) {
        m_text = text;
        return this;
    }
} // HlGui