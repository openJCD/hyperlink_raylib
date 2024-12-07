//
// Created by openjcd on 04/12/2024.
//

#include "CcOS.h"

#include <iostream>

#include "MarketplaceApp.h"
#include "OsProgram.h"
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


CcOS::CcOS(short screenWidth, short screenHeight) {
    CREATE_BUTTON_MEMBER_CALLBACK(_create_menu, f_create_menu);
    CREATE_BUTTON_MEMBER_CALLBACK(_close_menu, f_close_menu);
    CREATE_BUTTON_MEMBER_CALLBACK(_quit_game, f_quit);
    m_GuiScene.Begin(screenWidth, screenHeight);
        m_GuiScene.BeginControl<WindowControl>("Menu Window", 200, 250);
            m_GuiScene.CreateControl<Button>("Close Menu", f_close_menu);
            m_GuiScene.CreateControl<Button>("Quit", f_quit);
        m_Menu=m_GuiScene.EndControl<WindowControl>();
        m_GuiScene.CreateControl<Button>("Open Menu", f_create_menu);
    m_GuiRoot = m_GuiScene.End();
    m_Menu->Disable()->SetLayoutDirection(GUI_LAYOUT_VERTICAL);
    auto market = make_shared<MarketplaceApp>("Market", 0.5f);
    auto app1 = make_shared<OsProgram>("Cracker", 1.0f, "Sample application 1 for CcOS", 100);
    auto app2 = make_shared<OsProgram>("Uhhh", 1.0f, "Sample application 2 for CcOS", 150);
    m_ValidPrograms.emplace_back(market);
    m_ValidPrograms.emplace_back(app1);
    m_ValidPrograms.emplace_back(app2);

    market->ListApp(app1);
    market->ListApp(app2);
    LaunchProgram(market);
}

shared_ptr<Control> CcOS::GetRootGuiControl() {
    return m_GuiRoot;
}

shared_ptr<GuiScene> CcOS::GetGuiScene() {
    return make_shared<GuiScene>(m_GuiScene);
}

void CcOS::LaunchProgram(shared_ptr<OsProgram> program) {
    m_RunningPrograms.emplace_back(program);
    program->CreateWindow(make_shared<GuiScene>(m_GuiScene));
}
void CcOS::Update() {
    for (auto program: m_RunningPrograms) {
        program->OnUpdate();
    }
}