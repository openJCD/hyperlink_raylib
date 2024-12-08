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
class TerminalApp;
class NetworkNode;
using std::shared_ptr, std::list;
class OsProgram;
// class that contains a list of active processes, and a reference to the UI
// to allow for opening windows, etc
class CcOS {

    // -----Programs---- //
    map<string, shared_ptr<OsProgram>> m_ValidPrograms;
    list<shared_ptr<OsProgram>> m_RunningPrograms;

    shared_ptr<TerminalApp> m_TerminalProgram = nullptr;
    // ----------------- //

    // Player Data State //
    string       player_Username;
    string       player_Password;
    float        player_CreditBalance;
    NetworkNode* player_ConnectedNode;
    // ----------------- //

    // Gui state //
    GuiScene m_GuiScene;
    shared_ptr<Control> m_GuiRoot = nullptr;
    shared_ptr<WindowControl> m_Menu = nullptr;
    // ----------------- //

    // Gui Callbacks //
    void _create_menu(hl_ButtonEventArgs args);
    void _close_menu(hl_ButtonEventArgs args);
    void _quit_game(hl_ButtonEventArgs args);
    void _launch_program(hl_ButtonEventArgs args);
    // ---------------- //
public:
    CcOS(short screenWidth, short screenHeight);
    shared_ptr<Control> GetRootGuiControl();
    shared_ptr<GuiScene> GetGuiScene();
    void RegisterProgram(shared_ptr<OsProgram> program);
    void LaunchProgram(shared_ptr<OsProgram> program);
    void DeductPlayerCreditBalance(float amt) { player_CreditBalance-=amt; }
    void IncreasePlayerCreditBalance(float amt) { player_CreditBalance+=amt; }
    void TerminalLog(string msg);
    void Update();
};

#endif //HLOS_H
