//
// Created by openjcd on 08/12/2024.
//

#include "TerminalApp.h"

void TerminalApp::SendMessage(string msg) {
    m_textData += msg + '\n';
    if (m_textLabel != nullptr) {
        m_textLabel->SetText(m_textData.c_str());
    }
}

void TerminalApp::CreateWindow(shared_ptr<GuiScene> gui) {
    gui->Begin();
    gui->BeginControl<WindowControl>("Terminal", 300, 350);
        gui->CreateControl<LargeTextBox>(300,300,m_textData)->FillParentWidth()->SetColor(GREEN);
        gui->CreateControl<TextLabel>("Placeholder for text input field")->SetAlign(TEXT_ALIGN_LEFT)->FillParentWidth();
    m_GuiWindow = gui->EndControl<WindowControl>();
    m_GuiWindow->Disable();
    gui->End();
}

void TerminalApp::OnStartup() {
    OsProgram::OnStartup();
}
