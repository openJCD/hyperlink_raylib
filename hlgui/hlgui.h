//
// Created by openjcd on 01/12/2024.
//

#ifndef HLGUI_H
#define HLGUI_H
#include <memory>
#include <stack>

#include "Control.h"
#include "ResourceManager.h"

// gui styling methods
static void GuiSetGlobalFont(Font font) {
    ResourceManager::AddFont("default", font);
}
static void GuiSetDefaultStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("default", style);
}
static void GuiSetButtonStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("button", style);
}
static void GuiSetButtonHoveredStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("buttonHovered", style);
}
static void GuiSetWindowStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("window", style);
}
static void GuiSetTextLabelStyle(hl_StyleProperties style) {
    ResourceManager::AddStyle("textLabel", style);
}

// Gui layout state and ownership storage //

// stack of shared pointers to controls
static stack<shared_ptr<Control>> controlStack;

// stack of child counts to controls
static stack<int> controlChildCountStack;

// helper function for incrementing topmost child counter
void gui_incrememtCurrentChildCount() {
    if (controlChildCountStack.size() > 0) {
        int currentCount = controlChildCountStack.top();
        LOG("Incrememting child count: " + to_string(currentCount));
        controlChildCountStack.pop();
        controlChildCountStack.push(currentCount+1);
    }
}

// owned list of control objects
static list<Control> controlStorageList;

// the root control of the interface
static shared_ptr<Control> rootControlPtr;

static void GuiBegin(short windowWidth, short windowHeight) {
    rootControlPtr = make_shared<Control>(windowWidth, windowHeight, ANCHOR_TOP_LEFT);
    controlStorageList.push_front(*rootControlPtr);
    controlStack.push(rootControlPtr);
}

static Control& GuiEnd() {
    for (int i=0; i<controlStack.size(); i++) {
        shared_ptr<Control> control = controlStack.top();
        if (control == rootControlPtr) {
            break;
        } else {
            rootControlPtr->Add(controlStack.top());
            controlStack.pop();
        }
    }
    return *rootControlPtr;
}

static shared_ptr<Control> GuiCreateControl(short w, short h, hl_AnchorType anchor) {
    gui_incrememtCurrentChildCount();
    shared_ptr<Control> control = make_shared<Control>(w, h, anchor);

    controlStorageList.push_back(*control);
    controlStack.push(control);
    return control;
}

static void GuiBeginControl(short w, short h, hl_AnchorType anchor) {

    gui_incrememtCurrentChildCount();
    controlChildCountStack.push(0);

    shared_ptr<Control> control = make_shared<Control>(w, h, anchor);
    controlStorageList.push_back(*control);
    controlStack.push(control);
}

static shared_ptr<Control> GuiEndControl() {
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


#endif //HLGUI_H
