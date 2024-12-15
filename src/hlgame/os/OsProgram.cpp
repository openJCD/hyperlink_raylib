//
// Created by openjcd on 05/12/2024.
//

#include "OsProgram.h"

#include <iostream>

#include "../game_structs.h"

using std::move;

/// Open this program's GUI window
void OsProgram::OnStartup() {
    if (m_GuiWindow!=nullptr) {
        m_GuiWindow->Enable();
        m_GuiWindow->Activate();
    } else {
        GAME_LOG("Failed to open gui window for " + m_name + ". \nMake sure you set 'm_GuiWindow' to be your WindowControl in the CreateWindow function.");
    }
}
void OsProgram::OnShutdown() { }
void OsProgram::OnUpdate() { }
void OsProgram::CreateWindow(shared_ptr<GuiScene> gui) {
    CREATE_BUTTON_MEMBER_CALLBACK(_null_callback, f_null)
    gui->CreateControl<Button>("Hello World",f_null);
}

void OsProgram::DestroyWindow(shared_ptr<Control> guiRoot) {
    guiRoot->Remove(m_GuiWindow);
    delete m_GuiWindow.get();
}

/// returns the base cost at LEVEL_BASE, and the incremental increases after that.
float OsProgram::GetCostAt(hl_ProgramUpgradeLevel upgradeLevel) const {
    switch (upgradeLevel) {
        case PROGRAM_LEVEL_BASE:
            return m_baseCost;
        case PROGRAM_LEVEL_1:
            return m_upgradeCost1;
        case PROGRAM_LEVEL_2:
            return m_upgradeCost2;
        case PROGRAM_LEVEL_3:
            return m_upgradeCost3;
    }
    return 0;
}
