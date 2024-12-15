//
// Created by openjcd on 07/12/2024.
//

#ifndef MARKETPLACEAPP_H
#define MARKETPLACEAPP_H
#include "OsProgram.h"
#include "../game_structs.h"

class MarketplaceApp : public OsProgram {
private:
    map<string, shared_ptr<OsProgram>> m_purchasableApps;
    OsProgram* m_selectedApp = nullptr;
    shared_ptr<Button> btn_BuySell = nullptr;
    shared_ptr<Button> btn_Upgrade = nullptr;
    shared_ptr<Button> btn_Downgrade = nullptr;
public:
    MarketplaceApp(CcOS& gameState, const char *name, float minMemoryRequired)
        : OsProgram(gameState, name, minMemoryRequired) {
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
