//
// Created by openjcd on 29/11/2024.
//

#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H
#include "Button.h"
#include "TextLabel.h"
class WindowControl : public Control {
protected:
    string m_title = "Window";
    shared_ptr<TextLabel> m_titleBar = std::make_shared<TextLabel>(m_title.c_str());
    shared_ptr<Button> m_closeButton = make_shared<Button>("x", f_null_callback);
    hl_StyleProperties m_StyleProperties = ResourceManager::GetStyle("window");
    Font& m_titleFont = ResourceManager::GetFont("textLabel");

    void _close(hl_ClickEventArgs args);

    std::function<void()> _closeCallback;

    void PostDraw() override;
public:
    WindowControl(const char* title, short w, short h);


    WindowControl* SetTitle(const char* title);
    WindowControl* EnableCloseButton();

    WindowControl *OnClose(std::function<void()> callback);

    ~WindowControl() override;
};

#endif //WINDOWCONTROL_H