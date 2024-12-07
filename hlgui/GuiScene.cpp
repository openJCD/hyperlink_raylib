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
