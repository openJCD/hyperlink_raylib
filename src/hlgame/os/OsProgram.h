//
// Created by openjcd on 05/12/2024.
//

#ifndef OSPROGRAM_H
#define OSPROGRAM_H

#include <memory>
#include "../../hlgui/hlgui.h"

class CcOS;

enum hl_ProgramUpgradeLevel {
    PROGRAM_LEVEL_BASE,
    PROGRAM_LEVEL_1,
    PROGRAM_LEVEL_2,
    PROGRAM_LEVEL_3,
};

using std::shared_ptr, std::string;

class OsProgram {
protected:
    string m_name = "CcOS Program";
    string m_description = "A software package for CloudConnectOS";
    hl_ProgramUpgradeLevel m_upgradeLevel = PROGRAM_LEVEL_BASE;

    CcOS& m_CcOsState;

    float m_minRequiredMemory = 1.0f;

    int m_baseCost = 0;
    int m_upgradeCost1 = 50;
    int m_upgradeCost2 = 100;
    int m_upgradeCost3 = 150;
    bool m_isRunning = false;
    bool m_isOwned = false;
    void _null_callback(hl_ClickEventArgs args) {}
public:
    virtual ~OsProgram() = default;
    OsProgram(CcOS& gameState, const char* name, float minMemoryRequired, const char* description = "CcOS Program Executable", int baseCost = 0)
    : m_name(name), m_description(description), m_CcOsState(gameState), m_baseCost(baseCost), m_minRequiredMemory(minMemoryRequired) {};

    explicit OsProgram(CcOS& gameState) : m_CcOsState(gameState) {};

    virtual void OnStartup();
    virtual void OnUpdate();
    virtual void OnShutdown();

    [[nodiscard]] string GetName()          { return m_name; }
    [[nodiscard]] string GetDescription()   { return m_description; }
    [[nodiscard]] bool IsOwned() const      { return m_isOwned; }
    [[nodiscard]] float GetCostAt(hl_ProgramUpgradeLevel upgradeLevel) const;
    [[nodiscard]] hl_ProgramUpgradeLevel GetUpgradeLevel() const { return m_upgradeLevel; }

    void Upgrade() {
        if (m_upgradeLevel == PROGRAM_LEVEL_BASE) {
            m_upgradeLevel = PROGRAM_LEVEL_1;
        } else if (m_upgradeLevel == PROGRAM_LEVEL_1) {
            m_upgradeLevel = PROGRAM_LEVEL_2;
        } else if (m_upgradeLevel == PROGRAM_LEVEL_2) {
            m_upgradeLevel = PROGRAM_LEVEL_3;
        }
    }

    void Downgrade() {
        if (m_upgradeLevel == PROGRAM_LEVEL_3) {
            m_upgradeLevel = PROGRAM_LEVEL_2;
        } else if (m_upgradeLevel == PROGRAM_LEVEL_2) {
            m_upgradeLevel = PROGRAM_LEVEL_1;
        } else if (m_upgradeLevel == PROGRAM_LEVEL_1) {
            m_upgradeLevel = PROGRAM_LEVEL_BASE;
        }
    }

    void SetPurchased(bool state) { m_isOwned = state; }
};

#endif //OSPROGRAM_H
