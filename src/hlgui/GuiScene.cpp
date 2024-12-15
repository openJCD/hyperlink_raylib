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

stack<shared_ptr<Control>> GuiScene::_gui_reverseSomeOfStackUntil(int count) {
    stack<shared_ptr<Control>> stack_return;
    for (int i = 0; i < count; i++) {
        stack_return.push(controlStack.top());
        controlStack.pop();
    }
    return stack_return;
}

void GuiScene::Begin(short windowWidth, short windowHeight) {
    GUI_LOG("//-----------------------------------------------//");
    GUI_LOG("// -------Building the GUI ROOT LAYOUT!!!------- // ");
    rootControlPtr = make_shared<Control>(windowWidth, windowHeight, ANCHOR_TOP_LEFT);
    controlStorageList.push_front(*rootControlPtr);
    controlStack.push(rootControlPtr);
    controlChildCountStack.push(0);
}

void GuiScene::Begin(shared_ptr<Control> root)  {
    GUI_LOG("//-----------------------------------------------//");
    GUI_LOG("// -------Building the GUI ROOT LAYOUT!!!------- // ");
    rootControlPtr = root;
    controlStack.push(rootControlPtr);
    controlChildCountStack.push(0);
}

void GuiScene::Begin() {
    GUI_LOG("//-----------------------------------------------//");
    GUI_LOG("// -------Building the GUI ROOT LAYOUT!!!------- // ");
    if (rootControlPtr == nullptr) {
        throw null_gui_exception("Attempt to call Begin(void) with no pre-existing root control in the scene.");
    } else {
        controlStack.push(rootControlPtr);
        controlChildCountStack.push(0);
    }
}

shared_ptr<Control> GuiScene::End() {
    int childCount = controlChildCountStack.top();
    controlChildCountStack.pop();
    stack<shared_ptr<Control>> controlStackReversed = _gui_reverseSomeOfStackUntil(childCount);
    for (int i=0; i<childCount; i++) {
        shared_ptr<Control> control = controlStackReversed.top();
        if (control == rootControlPtr) {
            controlStackReversed.pop();
        } else {
            rootControlPtr->Add(controlStackReversed.top());
            controlStackReversed.pop();
        }
    }
    rootControlPtr->BaseLayout();
    GUI_LOG("// -------Finished the GUI ROOT LAYOUT!!!------- // ");
    GUI_LOG("//-----------------------------------------------//");
    return rootControlPtr;
}
