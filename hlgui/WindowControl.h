//
// Created by openjcd on 29/11/2024.
//

#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H
#include "TextLabel.h"
class WindowControl : public Control {
private:
    void Close();
protected:
    string m_title = "Window";
    TextLabel m_titleLabel = TextLabel("Window", ANCHOR_TOP);
    hl_StyleProperties m_StyleProperties = ResourceManager::GetStyle("window");
    void Draw() override;
public:
    WindowControl(short w, short h, hl_AnchorType startAnchor);
    Control* Add(Control *child) override;
    WindowControl* SetTitle(const char* title);
    ~WindowControl() override;
};

#endif //WINDOWCONTROL_H