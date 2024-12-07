#include "MarketplaceApp.h"
#include <iostream>

class ListBox;

MarketplaceApp::~MarketplaceApp() = default;

void MarketplaceApp::_purchase_software(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) {return;}
    if (m_selectedApp == nullptr) {return;}
    if (m_selectedApp->IsPurchased()) {
        GAME_LOG("Sold " + m_selectedApp->GetName());

        m_selectedApp->SetPurchased(false);
        btn_Upgrade->Deactivate();
        btn_Downgrade->Deactivate();
        btn_BuySell->SetText("Buy");
    } else {
        GAME_LOG("Bought " + m_selectedApp->GetName());

        m_selectedApp->SetPurchased(true);

        btn_BuySell->SetText("Sell");
    }
}

void MarketplaceApp::_upgrade_software(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) { return; }
    if (m_selectedApp == nullptr) { return; }
    GAME_LOG("Upgraded " + m_selectedApp->GetName() + " to level " + std::to_string(m_selectedApp->GetUpgradeLevel()+1));
    if (m_selectedApp->IsPurchased()) {
        m_selectedApp->Upgrade();
        btn_Downgrade->Activate();
        if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_3) {
            GAME_LOG("At max upgrade level.");
            btn_Upgrade->Deactivate();
        }
    }
}

void MarketplaceApp::_downgrade_software(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) { return; }
    if (m_selectedApp == nullptr) { return; }
    GAME_LOG("Downgraded " + m_selectedApp->GetName() + " to level " + std::to_string(m_selectedApp->GetUpgradeLevel()-1));
    m_selectedApp->Downgrade();
    btn_Upgrade->Activate();
    if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_BASE) {
        GAME_LOG("At minimum level.");
        btn_Downgrade->Deactivate();
    }
}

void MarketplaceApp::_select_app(Control* item) {
    if (item == nullptr) return;
    try {
        m_selectedApp = m_purchasableApps[item->GetTag()].get();
        if (m_selectedApp == nullptr) {
            return;
        } else {
            // the following checks are mostly just for basic UX.
            // if this app is already purchased, set the text to "sell", otherwise "buy".
            // if it is not already at max upgrade, activate "upgrade" button
            // if it is not at minimum upgrade level, activate "downgrade" button
            if (m_selectedApp->IsPurchased()) {
                btn_BuySell->SetText("Sell")->Activate();
                if (m_selectedApp->GetUpgradeLevel() != PROGRAM_LEVEL_3) {
                    btn_Upgrade->Activate();
                }
                if (m_selectedApp->GetUpgradeLevel() != PROGRAM_LEVEL_BASE) {
                    btn_Downgrade->Activate();
                }
            } else {
                btn_BuySell->SetText("Buy")->Activate();
                btn_Upgrade->Deactivate();
                btn_Downgrade->Deactivate();
            }
        }
    } catch (std::exception e){
        GAME_LOG("Failed to find the item " + item->GetTag() + " in the app list.");
    }
}

void MarketplaceApp::CreateWindow(shared_ptr<GuiScene> gui) {
    CREATE_BUTTON_MEMBER_CALLBACK(_purchase_software, f_purchase_software);
    CREATE_BUTTON_MEMBER_CALLBACK(_upgrade_software, f_upgrade_software);
    CREATE_BUTTON_MEMBER_CALLBACK(_downgrade_software, f_downgrade_software);
    CREATE_LIST_ITEM_MEMBER_CALLBACK(_select_app, f_select_app);
    gui->Begin();
        gui->BeginControl<WindowControl>("Marketplace", 300,250);
        gui->BeginControl<ListBox>(300,190,32);
        for (auto [name, app]: m_purchasableApps) {
            gui->BeginControl<Control>(300,32);
                gui->CreateControl<TextLabel>(app->GetName().c_str())->SetAnchor(ANCHOR_CENTER)->DisableMouseCapture();
            gui->EndControl<Control>()->SetTag(name.c_str());
        }
        gui->EndControl<ListBox>()->OnItemSelected(f_select_app)->SetPadding(0,0);
        gui->BeginControl<Control>(300,40);
            btn_BuySell   = gui->CreateControl<Button>("Buy", f_purchase_software);
            btn_BuySell->Deactivate();
            btn_Upgrade   = gui->CreateControl<Button>("Upgrade", f_upgrade_software);
            btn_Upgrade->Deactivate();
            btn_Downgrade = gui->CreateControl<Button>("Downgrade", f_downgrade_software);
            btn_Downgrade->Deactivate();
            gui->EndControl<Control>()->SetLayoutDirection(GUI_LAYOUT_HORIZONTAL)->SetBackgroundColor(TRANSPARENT)->SetPadding(0,0);
        gui->EndControl<WindowControl>();
    gui->End();
}

void MarketplaceApp::ListApp(shared_ptr<OsProgram> program) {
    m_purchasableApps[program->GetName()] = program;
}