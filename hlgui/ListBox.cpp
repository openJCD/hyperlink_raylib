//
// Created by openjcd on 07/12/2024.
//

#include "ListBox.h"

#include "hlgui.h"

void ListBox::Layout() {
    int cursorY = 0;
    for (auto child: m_Children) {
        child->SetLocalPos(0, cursorY);
        child->SetHeight(m_fixedItemHeight)->SetWidth(m_Bounds.width);
        cursorY+=m_fixedItemHeight;
    }
}

void ListBox::_item_select(hl_ButtonEventArgs args) {
    if (args.mask==MOUSE_MASK_DOWN) {
        if (m_selectedItem != nullptr) {
            m_selectedItem->SetBackgroundColor(m_StyleProperties.background_color);
            m_selectedItem->SetColor(m_StyleProperties.foreground_color);
        }
        m_selectedItem = args.sender;
        args.sender->SetBackgroundColor(ColorAlpha(m_StyleProperties.foreground_color, 0.25f));
        if (f_onItemSelect != nullptr)
            f_onItemSelect(args.sender);
    }
}

ListBox::ListBox(short width, short height, short fixedItemHeight) :Control(width, height), m_fixedItemHeight(fixedItemHeight) { }

Control* ListBox::Add(shared_ptr<Control> element) {
    CREATE_BUTTON_MEMBER_CALLBACK(_item_select, f_item_select)
    element->SetClickAction(f_item_select);
    return Control::Add(element);
}

ListBox * ListBox::OnItemSelected(std::function<void(Control*)> callback) {
    f_onItemSelect = callback;
    return this;
}
