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
    TextLabel m_titleLabel = TextLabel(m_title.c_str(), ANCHOR_TOP);
    void Draw() override;
public:
    WindowControl(short w, short h, hl_AnchorType startAnchor);
    Control* Add(Control* child) override;
    WindowControl* SetTitle(const char* title);
    ~WindowControl() override;
};

#endif //WINDOWCONTROL_H
