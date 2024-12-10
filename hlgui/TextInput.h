//
// Created by openjcd on 10/12/2024.
//

#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include "Control.h"

class TextInput : public Control {
private:
    void Backspace();
    void DeleteChar();
    void InsertChar(char c);
    void MoveLeftChar();
    void MoveRightChar();
    void MoveLeftWord();
    void MoveRightWord();
protected:
    string m_textContent;
    string m_hintText = "Write your input...";
    Font& m_font = ResourceManager::GetDefaultFont();

    int m_minPixelWidth;
    int m_maxPixelWidth;

    int m_cursorIndex=0;

    bool HasKeyboard = false;

    void Draw() override;
    void Update(float gameTime) override;
    void Layout() override;
public:
    TextInput(int minPixelWidth, int maxPixelWidth);
    TextInput(Font& font, int minPxelWidth, int maxPixelWidth);

    string GetText();
    TextInput* SetHintText(const char* text);
};



#endif //TEXTINPUT_H
