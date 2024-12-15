//
// Created by openjcd on 08/12/2024.
//

#ifndef LARGETEXTBOX_H
#define LARGETEXTBOX_H
#include "Control.h"


class LargeTextBox : public Control{
protected:
    void Draw() override;
    string m_text;
    Font& m_font = ResourceManager::GetFont("textLabel");

public:
    LargeTextBox(short w, short h, const string text)
        : Control(w, h),
          m_text(text) {
    }

    LargeTextBox(hl_AnchorType anchor, string text, Font &font)
        : Control(anchor),
          m_text(text),
          m_font(font) {
    }

    LargeTextBox(string text)
        : m_text(text) { }
    LargeTextBox* SetText(string text) {
        m_text = text;
        return this;
    }
};



#endif //LARGETEXTBOX_H
