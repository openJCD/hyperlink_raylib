//
// Created by openjcd on 04/12/2024.
//
#pragma once
#ifndef HLOS_H
#define HLOS_H
#include <list>
#include <memory>
#include "process.h"
#include "../../hlgui/GuiScene.h"
using std::shared_ptr, std::list;
class OsProgram;
// class that contains a list of active processes, and a reference to the UI
// to allow for opening windows, etc
class CcOS {
private:
    list<shared_ptr<OsProgram>> m_ValidPrograms;
    list<shared_ptr<OsProgram>> m_RunningPrograms;
    GuiScene m_GuiScene;
    shared_ptr<Control> m_GuiRoot = nullptr;

    // Gui state //
    shared_ptr<WindowControl> m_Menu;

    // Gui Creation Functions //
    void _create_menu(hl_ButtonEventArgs args);
    void _close_menu(hl_ButtonEventArgs args);

    void _quit_game(hl_ButtonEventArgs args);
public:
    CcOS(short screenWidth, short screenHeight);
    shared_ptr<Control> GetRootGuiControl();
    shared_ptr<GuiScene> GetGuiScene();
    void LaunchProgram(shared_ptr<OsProgram> program);
};

#endif //HLOS_H
