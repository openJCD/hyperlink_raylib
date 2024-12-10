//
// Created by openjcd on 10/12/2024.
//

#include "TextInput.h"

#include <valarray>

// Constructors //
TextInput::TextInput(const int minPixelWidth, const int maxPixelWidth) : Control(), m_minPixelWidth(minPixelWidth), m_maxPixelWidth(maxPixelWidth)  {}
TextInput::TextInput(Font &font, int minPixelWidth, int maxPixelWidth): m_font(font), m_minPixelWidth(minPixelWidth), m_maxPixelWidth(maxPixelWidth) {}
//--------------//

// Cursor/Char/Index helper functions //
void TextInput::Backspace() {
    if (!m_textContent.empty()) {
        if (m_cursorIndex > 0) {
            m_textContent.erase(m_cursorIndex, 1);
            m_cursorIndex-=1;
        }
    }
}

void TextInput::DeleteChar() {
    if (!m_textContent.empty()) {
        if (m_cursorIndex < m_textContent.size()) {
            m_textContent.erase(m_cursorIndex+1, 1);
        }
    }
}

void TextInput::InsertChar(const char c) {

    if (m_cursorIndex < m_textContent.length()-1) {
        if (m_textContent.length()>0)
            m_textContent.insert(m_cursorIndex+1, 1, c);
        else
            m_textContent+=c;
    } else {
        m_textContent+=c;
    }

    m_cursorIndex += 1;
}

void TextInput::MoveLeftChar() {
    if (m_cursorIndex > 0) {
        m_cursorIndex -= 1;
    }
}

void TextInput::MoveRightChar() {
    if (m_cursorIndex +1 < m_textContent.length()) {
        m_cursorIndex += 1;
    }
}

void TextInput::MoveLeftWord() {
    while (m_textContent[m_cursorIndex] != ' ') {
        if (m_cursorIndex > 0) {
            m_cursorIndex -= 1;
        }
    }
}
void TextInput::MoveRightWord() {
    while (m_textContent[m_cursorIndex] != ' ') {
        MoveRightChar();
    }
}
// ------------------------------- //

// Overriding Methods //
void TextInput::Draw() {
    Control::Draw();
    int textx = m_StyleProperties.margin.x;
    int texty = m_Bounds.height /2 - m_StyleProperties.font_size/2;

    int cursorPosX= m_StyleProperties.margin.x + (MeasureTextEx(m_font, m_textContent.substr(0, m_cursorIndex+1).c_str(), m_StyleProperties.font_size, 1).x);
    if (m_textContent.length() < m_hintText.length()) {
        DrawTextEx(m_font, m_textContent.c_str(), Vector2(textx, texty), m_StyleProperties.font_size, 1, m_StyleProperties.foreground_color);
    } else {
        DrawTextEx(m_font, m_textContent.c_str(), Vector2(textx, texty), m_StyleProperties.font_size, 1, ColorAlpha(m_StyleProperties.foreground_color, 127.5f));
    }
    if (HasKeyboard) {
        DrawLine(cursorPosX, m_StyleProperties.margin.y/2, cursorPosX, m_Bounds.height - m_StyleProperties.margin.y/2, m_StyleProperties.foreground_color);
    }
}

void TextInput::Update(float gameTime) {
    Control::Update(gameTime);
    if (HasKeyboard) {
        int key=GetCharPressed();
        while (key > 0) {
            InsertChar(key);
            key = GetCharPressed();
        }
        int kPress = GetKeyPressed();
        if (kPress == KEY_BACKSPACE) {
            Backspace();
        } else if (kPress == KEY_LEFT) {
            MoveLeftChar();
        } else if (kPress == KEY_RIGHT) {
            MoveRightChar();
        } else if (kPress == KEY_DELETE) {
            DeleteChar();
        }
    }
    if (IsHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HasKeyboard = true;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HasKeyboard = false;
    }
}

void TextInput::Layout() {
    // get the width. limit it to be between minimum and maximum pixel width
    m_Bounds.width = std::min(std::max( m_minPixelWidth, (int)MeasureTextEx(m_font, m_textContent.c_str(), m_StyleProperties.font_size, 1).x), m_maxPixelWidth);

    m_Bounds.height = MeasureTextEx(m_font, m_hintText.c_str(), m_StyleProperties.font_size, 1).y + m_StyleProperties.margin.y;

    Control::Layout();
}
//-------------------//
string TextInput::GetText() {
    return m_textContent;
}

TextInput* TextInput::SetHintText(const char *text) {
    m_hintText = text;
}