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
    hl_TextAlign m_alignMode = TEXT_ALIGN_CENTER;
    void Layout() override;
    void Update(float gameTime) override;
public:
    TextLabel(Font &font, const char* text);
    explicit TextLabel(const char *text);
    ~TextLabel() override;
    TextLabel *SetText(const char* text);
    TextLabel *SetAlign(hl_TextAlign alignMode);
};

#endif //TEXTLABEL_H
