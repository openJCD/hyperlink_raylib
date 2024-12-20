//
// Created by openjcd on 19/12/2024.
//

#ifndef OSGUIPROGRAM_H
#define OSGUIPROGRAM_H
#include "OsProgram.h"


class OsGuiProgram : public OsProgram {
protected:
    shared_ptr<WindowControl> m_GuiWindow;
public:
    void OnStartup() override;
    virtual void DestroyWindow(shared_ptr<Control> guiRoot);

    virtual void CreateWindow (shared_ptr<GuiScene> gui);

    explicit OsGuiProgram(CcOS& gameState) : OsProgram(gameState) {};
};



#endif //OSGUIPROGRAM_H
