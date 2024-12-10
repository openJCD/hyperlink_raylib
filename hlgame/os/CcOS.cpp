//
// Created by openjcd on 04/12/2024.
//

#include "CcOS.h"

#include <iostream>

#include "MarketplaceApp.h"
#include "OsProgram.h"
#include "TerminalApp.h"
#include "../../hlgui/FpsWidget.h"
#include "../../hlgui/hlgui.h"

void CcOS::_create_menu(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_BUTTON_LEFT) {return;}
    m_Menu->Enable();
}

void CcOS::_close_menu(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) {return;}
    m_Menu->Disable();
}

void CcOS::_quit_game(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) {return;}
    exit(0);
}
/// match the sender's tag to an app in the repository and launch that app if possible.
void CcOS::_launch_program(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) {return;}
    string programName = args.sender->GetTag();
    try {
        LaunchProgram(m_ValidPrograms[programName]);
    } catch (std::exception e) {
        TerminalLog("Failed to launch program " + programName);
        GAME_LOG("Failed to launch program " + programName);
    }
}

/// Initialise the game instance, creating the OS Graphical User Interface layout along with it.
CcOS::CcOS(short screenWidth, short screenHeight) {
    CREATE_BUTTON_MEMBER_CALLBACK(_create_menu, f_create_menu);
    CREATE_BUTTON_MEMBER_CALLBACK(_close_menu, f_close_menu);
    CREATE_BUTTON_MEMBER_CALLBACK(_quit_game, f_quit);
    CREATE_BUTTON_MEMBER_CALLBACK(_launch_program, f_launch_program);

    m_GuiScene.Begin(screenWidth, screenHeight);
        m_GuiScene.BeginControl<Control>(100,100);
            m_GuiScene.CreateControl<Button>("Open Menu", f_create_menu);
            m_GuiScene.CreateControl<Button>("Open Market", f_launch_program)->SetTag("Market");
            m_GuiScene.CreateControl<Button>("Open Terminal", f_launch_program)->SetTag("ccTerm");
        m_GuiScene.EndControl<Control>()->SetLayoutDirection(GUI_LAYOUT_HORIZONTAL);
        m_GuiScene.BeginControl<WindowControl>("Menu Window", 200, 250);
            m_GuiScene.CreateControl<Button>("Close Menu", f_close_menu);
            m_GuiScene.CreateControl<Button>("Quit", f_quit);
        m_Menu=m_GuiScene.EndControl<WindowControl>();
    m_GuiRoot = m_GuiScene.End();
    m_Menu->Disable()->SetLayoutDirection(GUI_LAYOUT_VERTICAL);

    auto market=make_shared<MarketplaceApp>(*this, "Market", 0.5f);
    auto app1 = make_shared<OsProgram>(*this, "PasswordCracker", 1.0f, "Sample application 1 for CcOS", 100);
    auto app2 = make_shared<OsProgram>(*this,"BotnetManager", 1.0f, "Sample application 2 for CcOS", 150);
    auto term = make_shared<TerminalApp>(*this);

    RegisterProgram(app1);
    RegisterProgram(app2);
    RegisterProgram(term);

    market->ListApp(app1);
    market->ListApp(app2);

    RegisterProgram(market);

    LaunchProgram(market);
}

shared_ptr<Control> CcOS::GetRootGuiControl() {
    return m_GuiRoot;
}

shared_ptr<GuiScene> CcOS::GetGuiScene() {
    return make_shared<GuiScene>(m_GuiScene);
}

void CcOS::RegisterProgram(shared_ptr<OsProgram> program) {
    m_ValidPrograms[program->GetName()] = program;
    program->CreateWindow(make_shared<GuiScene>(m_GuiScene));
}

void CcOS::LaunchProgram(shared_ptr<OsProgram> program) {
    m_RunningPrograms.emplace_back(program);
    program->OnStartup();
    TerminalLog("Started program " + program->GetName());
}

void CcOS::TerminalLog(string msg) {
    if (m_TerminalProgram != nullptr) {
        m_TerminalProgram->SendMessage(msg);
    }
}

void CcOS::Update() {
    for (auto program: m_RunningPrograms) {
        program->OnUpdate();
    }
}
