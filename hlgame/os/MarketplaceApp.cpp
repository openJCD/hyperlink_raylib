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
        if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_3) {
            GAME_LOG("At max upgrade level.");
        }
    }
}

void MarketplaceApp::_downgrade_software(hl_ButtonEventArgs args) {
    if (args.mask != MOUSE_MASK_UP) { return; }
    if (m_selectedApp == nullptr) { return; }
    GAME_LOG("Downgraded " + m_selectedApp->GetName() + " to level " + std::to_string(m_selectedApp->GetUpgradeLevel()-1));
    m_selectedApp->Downgrade();
    if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_BASE) {
        GAME_LOG("At minimum level.");
    }
}

void MarketplaceApp::_select_app(Control* item) {
    if (item == nullptr) return;
    try {
        m_selectedApp = m_purchasableApps[item->GetTag()].get();
        if (m_selectedApp == nullptr) {
            return;
        } else {
            if (m_selectedApp->IsPurchased()) {
                btn_BuySell->SetText("Sell")->Activate();

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
        gui->BeginControl<ListBox>(300,190);
        for (const auto& [name, app]: m_purchasableApps) {
            gui->CreateControl<TextLabel>((app->GetName() + " v" + to_string(app->GetUpgradeLevel()+1)).c_str() )->SetTag(name.c_str())->SetPadding(0,0)->FillParentWidth();
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
        m_GuiWindow = gui->EndControl<WindowControl>();
    gui->End();
}

void MarketplaceApp::ListApp(shared_ptr<OsProgram> program) {
    m_purchasableApps[program->GetName()] = program;
}
void MarketplaceApp::OnUpdate() {
    OsProgram::OnUpdate();
    if (m_selectedApp != nullptr) {
        btn_BuySell->Activate();
        btn_Upgrade->Activate();
        btn_Downgrade->Activate();
        if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_BASE) {
            btn_Downgrade->Deactivate();
        }
        if (m_selectedApp->GetUpgradeLevel() == PROGRAM_LEVEL_3) {
            btn_Upgrade->Deactivate();
        }
        if (!m_selectedApp->IsPurchased()) {
            btn_Upgrade->Deactivate();
            btn_Downgrade->Deactivate();
        }
    } else {
        btn_BuySell->Deactivate();
        btn_Upgrade->Deactivate();
        btn_Downgrade->Deactivate();
    }
}
