﻿//
// Created by openjcd on 05/12/2024.
//
#pragma once
#ifndef GUISCENE_H
#define GUISCENE_H
#include <iostream>
#include <list>
#include <stack>

#include "Control.h"
#include "WindowControl.h"
#include "TextLabel.h"
#include "Button.h"
#include "gui_structs.h"
#include "ListBox.h"
#include "FpsWidget.h"
#include "LargeTextBox.h"
#include "TextInput.h"

using std::list, std::stack, std::make_shared;

class GuiScene {
private:
    // stack of shared pointers to controls
    stack<shared_ptr<Control>> controlStack;

    // stack of child counts for controls
    stack<int> controlChildCountStack;

    // owned list of control objects
    list<Control> controlStorageList;

    // shared pointer to the root control of the interface
    shared_ptr<Control> rootControlPtr;

    // helper function for incrementing topmost child counter
    void _gui_incrememtCurrentChildCount();

    // helper function to take <count> items from the control stack and return a reversed copy of that section.
    stack<shared_ptr<Control>> _gui_reverseSomeOfStackUntil(int count);
public:
    /// begin the GUI layout, creating a new root control
    void Begin(short windowWidth, short windowHeight);
    /// begin the GUI layout again with an existing root control
    void Begin(shared_ptr<Control> root);

    /// begin the GUI layout again with the same root control.
    /// @throws null_gui_exception if root is null (not instantiated)
    void Begin();

    /// finish the current GUI layout and add tree to the root control.
    shared_ptr<Control> End();

    /// create a standalone, empty control
    template<class ControlType, typename... Args>
    shared_ptr<ControlType> CreateControl(Args... args){
        GUI_LOG("//-----------------------------------------------//");
        GUI_LOG(TextFormat("// -------Building a standalone %s ------- // ", typeid(ControlType).name()));
        static_assert(std::is_base_of<Control, ControlType>(), "GUI ERROR: Given type must be a subclass of Control.");
        _gui_incrememtCurrentChildCount();
        shared_ptr<ControlType> control = make_shared<ControlType>(args...);
        controlStorageList.push_back(*control);
        controlStack.push(control);
        control->BaseLayout();
        GUI_LOG(TextFormat("// -------Finished the standalone %s------- // ", typeid(ControlType).name()));
        GUI_LOG("//-----------------------------------------------//");
        return control;
    }

    /// begin a new control layout. declare children below.
    template<class ControlType, typename... Args>
    void BeginControl(Args... args) {
        GUI_LOG("//-----------------------------------------------//");
        GUI_LOG(TextFormat("// -------Building a %s with children------ // ", typeid(ControlType).name()));
        static_assert(std::is_base_of<Control, ControlType>(), "GUI ERROR: Given type must be a subclass of Control.");

        _gui_incrememtCurrentChildCount();
        controlChildCountStack.push(0);

        shared_ptr<ControlType> control = make_shared<ControlType>(args...);
        controlStorageList.emplace_back(*control);
        controlStack.push(control);
    }

    /// finish the current control layout and add all above child controls.
    template<class ControlType>
    shared_ptr<ControlType> EndControl() {
        static_assert(std::is_base_of<Control, ControlType>(), "GUI ERROR: Given type must be a subclass of Control.");

        list<shared_ptr<Control>> ptrsToAdd;

        // stack must be reversed up until the end of my nested children, as otherwise they are ordered and layed out wrong.
        stack<shared_ptr<Control>> controlStackReversed = _gui_reverseSomeOfStackUntil(controlChildCountStack.top());
        controlChildCountStack.pop();

        int count = controlStackReversed.size();
        for (int i=0; i<count; i++) {
            shared_ptr<Control> control = controlStackReversed.top();
            ptrsToAdd.push_back(control);
            controlStackReversed.pop();
        }

        shared_ptr<ControlType> myself = std::dynamic_pointer_cast<ControlType>(controlStack.top());
        for (const auto& ptr: ptrsToAdd) {
            myself->Add(ptr);
        }
        myself->BaseLayout();
        GUI_LOG(TextFormat("// -------Finished a %s with %i children------ // ", typeid(ControlType).name(), count));
        GUI_LOG("//-----------------------------------------------//");
        return myself;
    }
};

#endif // GUISCENE_H