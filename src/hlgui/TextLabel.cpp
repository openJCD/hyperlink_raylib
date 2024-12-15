//
// Created by openjcd on 28/11/2024.
//

#include "TextLabel.h"

void TextLabel::Draw() {
    Control::Draw();
    Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_StyleProperties.font_size, 1);
    int textx = 0;
    int texty = 0;
    switch (m_alignMode) {
        case TEXT_ALIGN_LEFT:
            textx = (int)(m_StyleProperties.margin.x);
            texty = (int)(m_Bounds.height/2 - textSize.y / 2);
            break;
        case TEXT_ALIGN_CENTER:
            textx = (int)(m_Bounds.width/2 - textSize.x / 2);
            texty = (int)(m_Bounds.height/2 - textSize.y / 2);
            break;
        case TEXT_ALIGN_RIGHT:
            textx = (int)(m_Bounds.width - textSize.x - m_StyleProperties.margin.x);
            texty = (int)(m_Bounds.height/2 - textSize.y / 2);
            break;
    }

    DrawTextEx(m_font, m_text.c_str(), Vector2(textx, texty), m_StyleProperties.font_size, 1, m_StyleProperties.foreground_color);
}

void TextLabel::Layout() {
    Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_StyleProperties.font_size, 1);
    m_Bounds = Rectangle(m_Bounds.x, m_Bounds.y, textSize.x+m_StyleProperties.margin.x*2, textSize.y+m_StyleProperties.margin.y);
    Control::Layout();
}

TextLabel::TextLabel(Font &font, const char* text) : Control() {
    m_text = text;
    _debug_string = "TextLabel_'" + string(text) + "'";
    m_font = font;
    Control::SetStyle(ResourceManager::GetStyle("textLabel"));
    Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_StyleProperties.font_size, 1);
    m_Bounds = Rectangle(m_Bounds.x, m_Bounds.y, textSize.x+m_StyleProperties.margin.x*2, textSize.y+m_StyleProperties.margin.y);
}
TextLabel::TextLabel(const char* text) : Control() {
    m_text = text;
    _debug_string = "TextLabel_'" + string(text) + "'";
    Control::SetStyle(ResourceManager::GetStyle("textLabel"));
    Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_StyleProperties.font_size, 1);
    m_Bounds = Rectangle(m_Bounds.x, m_Bounds.y, textSize.x+m_StyleProperties.margin.x*2, textSize.y+m_StyleProperties.margin.y);
}

TextLabel::~TextLabel() {
    m_text.clear();
}

// end data binding functions

void TextLabel::Update(float gameTime) {
    this->Control::Update(gameTime);
}

TextLabel * TextLabel::SetText(const char *text) {
    m_text = text;
    Redraw=true;
    BaseLayout();
    return this;
}

TextLabel * TextLabel::SetAlign(hl_TextAlign alignMode) {
    m_alignMode = alignMode;
    Redraw=true;
    return this;
}
