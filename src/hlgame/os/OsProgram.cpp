//
// Created by openjcd on 05/12/2024.
//

#include "OsProgram.h"

#include <iostream>

#include "../game_structs.h"

using std::move;

/// Open this program's GUI window
void OsProgram::OnStartup() {

}
void OsProgram::OnShutdown() { }

void OsProgram::OnUpdate() { }


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
