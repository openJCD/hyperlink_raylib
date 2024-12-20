//
// Created by openjcd on 19/12/2024.
//

#include "OsGuiProgram.h"
void OsGuiProgram::OnStartup() {
    m_GuiWindow->Enable();
    m_GuiWindow->Activate();
}
void OsGuiProgram::CreateWindow(shared_ptr<GuiScene> gui) {
    CREATE_BUTTON_MEMBER_CALLBACK(_null_callback, f_null)
    gui->Begin();
        gui->BeginControl<WindowControl>("Window", 400, 450);
            gui->CreateControl<Button>("Hello World",f_null);
        m_GuiWindow = gui->EndControl<WindowControl>();
    gui->End();
    m_GuiWindow->Disable();
}
void OsGuiProgram::DestroyWindow(shared_ptr<Control> guiRoot) {
    guiRoot->Remove(m_GuiWindow);
    delete m_GuiWindow.get();
}

