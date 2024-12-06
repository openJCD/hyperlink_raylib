﻿//
// Created by openjcd on 04/12/2024.
//

#include "CcOS.h"

#include <iostream>

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
        m_GuiScene.CreateButton("Open Menu", f_create_menu, ANCHOR_TOP_LEFT);
        m_GuiScene.BeginControl<WindowControl>("Menu Window", 200, 250, ANCHOR_CENTER);
            m_GuiScene.CreateButton("Quit", f_quit, ANCHOR_TOP_LEFT);
            m_GuiScene.CreateButton("Resume", f_close_menu, ANCHOR_TOP_LEFT);
            m_GuiScene.CreateControl<TextLabel>("Hello!", ANCHOR_TOP_RIGHT);
        m_Menu=m_GuiScene.EndControl<WindowControl>();
    m_GuiRoot = m_GuiScene.End();
    m_Menu->Disable();
}

shared_ptr<Control> CcOS::GetRootGuiControl() {
    return m_GuiRoot;
}

shared_ptr<GuiScene> CcOS::GetGuiScene() {
    return make_shared<GuiScene>(m_GuiScene);
}
