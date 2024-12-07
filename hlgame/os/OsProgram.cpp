//
// Created by openjcd on 05/12/2024.
//

#include "OsProgram.h"

using std::move;
void OsProgram::OnStartup() { }
void OsProgram::OnShutdown() { }
void OsProgram::OnUpdate() { }
void OsProgram::CreateWindow(shared_ptr<GuiScene> gui) {
    CREATE_BUTTON_MEMBER_CALLBACK(_null_callback, f_null)
    gui->Begin();
    gui->BeginControl<WindowControl>(m_name.c_str(), 200,200);
    gui->CreateControl<Button>("Hello World",f_null);
    gui->EndControl<WindowControl>();
    gui->End();
}

void OsProgram::DestroyWindow(shared_ptr<Control> guiRoot) {
    guiRoot->Remove(m_GuiWindow);
    delete m_GuiWindow.get();
}
