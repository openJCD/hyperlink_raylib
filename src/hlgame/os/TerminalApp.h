//
// Created by openjcd on 08/12/2024.
//

#ifndef TERMINALAPP_H
#define TERMINALAPP_H
#include "OsGuiProgram.h"
#include "OsProgram.h"

class TerminalApp : public OsGuiProgram {
private:
    string    m_textData = "Welcome to the CcOS Terminal Emulator v1.2";
    shared_ptr<LargeTextBox> m_textLog;
    shared_ptr<Control> m_contextMenu;
    void _receive_command(TextInput &sender);
    void _open_context_menu(hl_ClickEventArgs args);
    void _close_context_menu(hl_ClickEventArgs args);

    Model m_pcModel;
public:
    TerminalApp(CcOS &gameState)
        : OsGuiProgram(gameState) {
        m_description = "CcOS builtin blazing-fast terminal emulator";
        m_name = "//ccTerm";
        m_isOwned = true;
    }

    void SendMessage(string msg);

    void CreateWindow(shared_ptr<GuiScene> gui) override;
};



#endif //TERMINALAPP_H
