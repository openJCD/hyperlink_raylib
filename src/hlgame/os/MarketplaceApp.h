//
// Created by openjcd on 07/12/2024.
//

#ifndef MARKETPLACEAPP_H
#define MARKETPLACEAPP_H
#include "OsGuiProgram.h"
#include "OsProgram.h"
#include "../game_structs.h"

class MarketplaceApp : public OsGuiProgram {
private:
    map<string, shared_ptr<OsProgram>> m_purchasableApps;
    OsProgram* m_selectedApp = nullptr;
    shared_ptr<Button> btn_BuySell = nullptr;
    shared_ptr<Button> btn_Upgrade = nullptr;
    shared_ptr<Button> btn_Downgrade = nullptr;
public:
    MarketplaceApp(CcOS& gameState) : OsGuiProgram(gameState) {
        m_name = "//marketplace";
        m_description = "Black-market hacking software can be purchased and upgraded here.";
    }

    ~MarketplaceApp() override;

    void _purchase_software(hl_ClickEventArgs args);

    void _upgrade_software(hl_ClickEventArgs args);

    void _downgrade_software(hl_ClickEventArgs args);

    void _select_app(Control *item);

    void CreateWindow(shared_ptr<GuiScene> gui) override;

    void ListApp(shared_ptr<OsProgram> program);

    void OnUpdate() override;
};
#endif //MARKETPLACEAPP_H
