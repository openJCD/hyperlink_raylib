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
    Font m_font = ResourceManager::GetDefaultFont();
    void RecalculateBounds() override;
public:
    TextLabel(Font &font, const char* text, hl_AnchorType anchor);

    TextLabel(const char *text, hl_AnchorType anchor);

    ~TextLabel() override;
    void Update(float gameTime) override;
    TextLabel *SetText(const char* text);
};


#endif //TEXTLABEL_H
