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

    void BackspaceWord();

    void DeleteWord();

protected:
    string m_textContent;
    string m_hintText = "Write your input...";
    Font& m_font = ResourceManager::GetDefaultFont();

    int m_minPixelWidth;
    int m_maxPixelWidth;

    int m_cursorIndex=0;

    bool HasKeyboard = false;

    std::function<void(TextInput&, char)> f_onCharEntered = nullptr;
    std::function<void(TextInput&)> f_onReturnPressed = nullptr;
    void Draw() override;
    void Update(float gameTime) override;
    void Layout() override;
public:
    TextInput(int minPixelWidth, int maxPixelWidth);
    TextInput(Font& font, int minPxelWidth, int maxPixelWidth);

    string GetText();

    TextInput* SetOnReturnCallback(std::function<void(TextInput&)> callback);
    TextInput* SetOnCharEnteredCallback(std::function<void(TextInput&, char)> callback);

    TextInput* SetHintText(const char* text);
};



#endif //TEXTINPUT_H
