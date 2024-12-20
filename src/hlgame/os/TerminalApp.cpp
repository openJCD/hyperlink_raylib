//
// Created by openjcd on 08/12/2024.
//

#include "TerminalApp.h"

#include <io.h>

#include "../../hlgui/Orbital3DBackgroundControl.h"

void TerminalApp::_receive_command(TextInput &sender) {
    // change this code later to instruct the OS to execute commands rather than just sending a debug message
    SendMessage("Got command: " + sender.GetText());
}

void TerminalApp::_open_context_menu(hl_ClickEventArgs args) {
    if (args.button==MOUSE_BUTTON_RIGHT && args.mask == MOUSE_MASK_UP) {
        if (m_contextMenu!=nullptr) {
            m_contextMenu->SetLocalPos((short)GetMousePosition().x - m_GuiWindow->GetBounds().x, (short)GetMousePosition().y - m_GuiWindow->GetBounds().y);
            GUI_LOG(TextFormat("Enabled context menu. Global pos : %i %i, Parent position: %i %i", GetMouseX(), GetMouseY(), m_GuiWindow->GetBounds().x, m_GuiWindow->GetBounds().y));
            m_contextMenu->Enable();
        }
    }
}

void TerminalApp::_close_context_menu(hl_ClickEventArgs args) {
    if (args.button==MOUSE_BUTTON_LEFT && args.mask == MOUSE_MASK_UP) {
        if (m_contextMenu!=nullptr) {
            m_contextMenu->Disable();
        }
    }
}

void TerminalApp::SendMessage(string msg) {
    m_textData += msg + '\n';
    if (m_textLog != nullptr) {
        m_textLog->SetText(m_textData.c_str());
    }
}

void TerminalApp::CreateWindow(shared_ptr<GuiScene> gui) {
    CREATE_TEXTINPUT_CALLBACK(_receive_command, f_receive_command)
    CREATE_BUTTON_MEMBER_CALLBACK(_open_context_menu, f_open_context_menu)
    CREATE_BUTTON_MEMBER_CALLBACK(_close_context_menu, f_close_context_menu);
    gui->Begin();
        gui->BeginControl<WindowControl>("Terminal", 300, 350);
            gui->CreateControl<Orbital3DBackgroundControl>(ResourceManager::GetModel("pc"))->SetFloating()->FillParentWidth()->FillParentHeight()->SetPadding(0,0);
            m_textLog = gui->CreateControl<LargeTextBox>(300, 300,m_textData);
                m_textLog->SetClickAction(f_open_context_menu)->FillParentWidth();
            gui->CreateControl<TextInput>(300, 300)->SetOnReturnCallback(f_receive_command)->FillParentWidth();
        m_GuiWindow = gui->EndControl<WindowControl>();
    gui->End();
    m_GuiWindow->Disable();
}