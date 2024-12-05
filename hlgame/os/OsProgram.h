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
    hl_ProgramUpgradeLevel m_upgradeLevel = PROGRAM_LEVEL_BASE;
    float m_minRequiredMemory = 1.0f;
    shared_ptr<WindowControl> m_GuiWindow;
    bool m_isRunning = false;
public:
    virtual ~OsProgram() = default;
    OsProgram(const char* name, float minMemoryRequired) : m_name(name), m_minRequiredMemory(minMemoryRequired) {};
    virtual void OnStartup();
    virtual void OnUpdate();
    virtual void OnShutdown();
    virtual void CreateWindow(shared_ptr<GuiScene> gui);
    void         DestroyWindow(shared_ptr<Control> guiRoot);
};

#endif //OSPROGRAM_H
