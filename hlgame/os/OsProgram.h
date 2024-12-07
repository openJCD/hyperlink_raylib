//
// Created by openjcd on 05/12/2024.
//

#ifndef OSPROGRAM_H
#define OSPROGRAM_H

#include <memory>
#include "../../hlgui/hlgui.h"

enum hl_ProgramUpgradeLevel {
    PROGRAM_LEVEL_BASE,
    PROGRAM_LEVEL_1,
    PROGRAM_LEVEL_2,
    PROGRAM_LEVEL_3,
};

using std::shared_ptr, std::string;

class OsProgram {
    string m_name;
    string m_description;
    hl_ProgramUpgradeLevel m_upgradeLevel = PROGRAM_LEVEL_BASE;
    shared_ptr<WindowControl> m_GuiWindow;

    int m_baseCost = 0;
    int m_upgradeCost1 = 50;
    int m_upgradeCost2 = 100;
    int m_upgradeCost3 = 150;
    float m_minRequiredMemory = 1.0f;
    bool m_isRunning = false;
    bool m_isPurchased = false;
    void _null_callback(hl_ButtonEventArgs args) {}
public:
    virtual ~OsProgram() = default;
    OsProgram(const char* name, float minMemoryRequired, const char* description = "CcOS Program Executable", int baseCost = 0)
    : m_name(name), m_minRequiredMemory(minMemoryRequired), m_description(description), m_baseCost(baseCost) {};
    virtual void OnStartup();
    virtual void OnUpdate();
    virtual void OnShutdown();
    virtual void CreateWindow(shared_ptr<GuiScene> gui);
    void         DestroyWindow(shared_ptr<Control> guiRoot);

    string GetName() { return m_name; }
    hl_ProgramUpgradeLevel GetUpgradeLevel() const { return m_upgradeLevel; }
    bool IsPurchased() { return m_isPurchased; }
    string GetDescription() { return m_description; }
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

    void SetPurchased(bool state) { m_isPurchased = state; }
};

#endif //OSPROGRAM_H
