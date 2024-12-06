//
// Created by openjcd on 29/11/2024.
//

#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H
#include "TextLabel.h"
class WindowControl : public Control {
protected:
    string m_title = "Window";
    TextLabel m_titleLabel = TextLabel("Window");
    Control m_innerControl = Control();
    hl_StyleProperties m_StyleProperties = ResourceManager::GetStyle("window");
    void Draw() override;
public:
    WindowControl(const char* title, short w, short h);
    Control* Add(shared_ptr<Control> child) override;
    WindowControl* SetTitle(const char* title);
    ~WindowControl() override;
};

#endif //WINDOWCONTROL_H