//
// Created by openjcd on 28/11/2024.
//

#ifndef TEXTLABEL_H
#define TEXTLABEL_H
#include <string>
#include "Control.h"
#include "ResourceManager.h"

class TextLabel : public Control {
protected:
    void Draw() override;
    string m_text = "Label";
    hl_AnchorType m_Anchor = ANCHOR_AUTO;
    Font& m_font = ResourceManager::GetDefaultFont();
    void Layout() override;
public:
    TextLabel(Font &font, const char* text);
    explicit TextLabel(const char *text);
    ~TextLabel() override;
    void Update(float gameTime) override;
    TextLabel *SetText(const char* text);
};

#endif //TEXTLABEL_H
