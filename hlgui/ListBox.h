//
// Created by openjcd on 07/12/2024.
//

#ifndef LISTBOX_H
#define LISTBOX_H
#include "Control.h"


class ListBox : public Control {
protected:
    void Layout() override;
    Control* m_selectedItem = nullptr;
    void _item_select(hl_ButtonEventArgs args);
    std::function<void(Control*)> f_onItemSelect;
public:
    ListBox(short width, short height);
    Control* Add(shared_ptr<Control> control) override;
    ListBox* OnItemSelected(std::function<void(Control *)> callback);
};

#endif //LISTBOX_H
