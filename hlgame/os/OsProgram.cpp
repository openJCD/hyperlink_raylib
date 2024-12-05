//
// Created by openjcd on 05/12/2024.
//

#include "OsProgram.h"

using std::move;
void OsProgram::OnStartup() { }
void OsProgram::OnShutdown() { }
void OsProgram::OnUpdate() { }
void OsProgram::CreateWindow(shared_ptr<GuiScene> gui) {
    gui->Begin();
    gui->BeginWindow(m_name.c_str(), 200,200,ANCHOR_CENTER);
    gui->CreateButton("Hello World",nullptr, ANCHOR_BOTTOM_RIGHT);
    gui->EndWindow();
    gui->End();
}

void OsProgram::DestroyWindow(shared_ptr<Control> guiRoot) {
    guiRoot->Remove(m_GuiWindow);
    delete m_GuiWindow.get();
}
