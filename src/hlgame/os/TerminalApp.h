//
// Created by openjcd on 08/12/2024.
//

#ifndef TERMINALAPP_H
#define TERMINALAPP_H
#include "OsProgram.h"

class TerminalApp : public OsProgram {
private:
    string    m_textData = "Welcome to the CcOS Terminal Emulator v1.2";
    shared_ptr<LargeTextBox> m_textLog;
    shared_ptr<Control> m_contextMenu;
    void _receive_command(TextInput &sender);
    void _open_context_menu(hl_ClickEventArgs args);
    void _close_context_menu(hl_ClickEventArgs args);
public:
    TerminalApp(CcOS &gameState)
        : OsProgram(gameState) {
        m_description = "CcOS builtin blazing-fast terminal emulator";
        m_name = "ccTerm";
        m_isPurchased = true;
    }

    void SendMessage(string msg);

    void OnStartup() override;

    void CreateWindow(shared_ptr<GuiScene> gui) override;
};



#endif //TERMINALAPP_H
