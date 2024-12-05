//
// Created by openjcd on 05/12/2024.
//

#include "GuiScene.h"

void GuiScene::_gui_incrememtCurrentChildCount() {
    if (!controlChildCountStack.empty()) {
        int currentCount = controlChildCountStack.top();
        controlChildCountStack.pop();
        controlChildCountStack.push(currentCount+1);
    }
}

void GuiScene::Begin(short windowWidth, short windowHeight) {
    rootControlPtr = make_shared<Control>(windowWidth, windowHeight, ANCHOR_TOP_LEFT);
    controlStorageList.push_front(*rootControlPtr);
    controlStack.push(rootControlPtr);
}

void GuiScene::Begin(shared_ptr<Control> root)  {
    rootControlPtr = root;
    controlStack.push(rootControlPtr);
}

void GuiScene::Begin() {
    if (rootControlPtr == nullptr) {
        throw null_gui_exception("Attempt to call Begin(void) with no pre-existing root control in the scene.");
    } else {
        controlStack.push(rootControlPtr);
    }
}

shared_ptr<Control> GuiScene::End() {
    for (int i=0; i<controlStack.size(); i++) {
        shared_ptr<Control> control = controlStack.top();
        if (control == rootControlPtr) {
            controlStack.pop();
        } else {
            rootControlPtr->Add(controlStack.top());
            controlStack.pop();
        }
    }
    return rootControlPtr;
}

shared_ptr<Control> GuiScene::CreateControl(short w, short h, hl_AnchorType anchor) {
    _gui_incrememtCurrentChildCount();
    shared_ptr<Control> control = make_shared<Control>(w, h, anchor);

    controlStorageList.push_back(*control);
    controlStack.push(control);
    return control;
}

void GuiScene::BeginControl(short w, short h, hl_AnchorType anchor) {
    _gui_incrememtCurrentChildCount();
    controlChildCountStack.push(0);

    shared_ptr<Control> control = make_shared<Control>(w, h, anchor);
    controlStorageList.push_back(*control);
    controlStack.push(control);
}

shared_ptr<Control> GuiScene::EndControl() {
    list<shared_ptr<Control>> ptrsToAdd;
    for (int i=0; i<controlChildCountStack.top(); i++) {
        shared_ptr<Control> control = controlStack.top();
        ptrsToAdd.push_back(control);
        controlStack.pop();
    }
    controlChildCountStack.pop();
    auto myself = controlStack.top();
    for (const auto& ptr: ptrsToAdd) {
        myself->Add(ptr);
    }
    return myself;
}

void GuiScene::BeginWindow(const char *title, short w, short h, hl_AnchorType anchor) {
    _gui_incrememtCurrentChildCount();
    controlChildCountStack.push(0);

    shared_ptr<WindowControl> control = make_shared<WindowControl>(w, h, anchor);
    windowControlStorageList.push_back(*control);
    control->SetTitle(title);
    controlStack.push(control);
}

shared_ptr<WindowControl> GuiScene::EndWindow() {
    list<shared_ptr<Control>> ptrsToAdd;
    for (int i=0; i<controlChildCountStack.top(); i++) {
        shared_ptr<Control> control = controlStack.top();
        ptrsToAdd.push_back(control);
        controlStack.pop();
    }
    controlChildCountStack.pop();
    shared_ptr<WindowControl> myself = std::dynamic_pointer_cast<WindowControl>(controlStack.top());
    for (const auto& ptr: ptrsToAdd) {
        myself->Add(ptr);
    }
    return myself;
}
shared_ptr<Button> GuiScene::CreateButton(const char *text, std::function<void(hl_ButtonEventArgs)> onclick, hl_AnchorType anchor) {
    _gui_incrememtCurrentChildCount();
    shared_ptr<Button> button = make_shared<Button>(text, onclick, anchor);

    buttonStorageList.push_back(*button);
    controlStack.push(button);
    return button;
}

