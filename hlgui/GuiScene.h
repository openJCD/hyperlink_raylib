//
// Created by openjcd on 05/12/2024.
//

#ifndef GUISCENE_H
#define GUISCENE_H
#include <list>
#include <stack>

#include "Control.h"
#include "WindowControl.h"
#include "TextLabel.h"
#include "Button.h"
#include "gui_structs.h"
using std::list, std::stack, std::make_shared;

class GuiScene {
private:

    // stack of shared pointers to controls
    stack<shared_ptr<Control>> controlStack;

    // stack of child counts for controls
    stack<int> controlChildCountStack;

    // helper function for incrementing topmost child counter
    void _gui_incrememtCurrentChildCount();
    // owned list of control objects
    list<Control> controlStorageList;
    // owned list of window controls
    list<WindowControl> windowControlStorageList;
    // owned list of text labels
    list<TextLabel> textLabelStorageList;
    // owned list of buttons
    list<Button> buttonStorageList;
    // shared pointer to the root control of the interface
    shared_ptr<Control> rootControlPtr;

public:
    /// begin the GUI layout, creating a new root control
    void Begin(short windowWidth, short windowHeight);
    /// begin the GUI layout again with an existing root control
    void Begin(shared_ptr<Control> root);

    /// begin the GUI layout again with the same root control
    void Begin();
    /// finish the current GUI layout and add tree to the root control.
    shared_ptr<Control> End();
    /// create a standalone, empty control
    shared_ptr<Control> CreateControl(short w, short h, hl_AnchorType anchor);
    /// begin a new control layout. declare children below.
    void BeginControl(short w, short h, hl_AnchorType anchor);
    /// finish the current control layout and add all above child controls.
    shared_ptr<Control> EndControl();

    void BeginWindow(const char* title, short w, short h, hl_AnchorType anchor);
    shared_ptr<WindowControl> EndWindow();
    shared_ptr<Button> CreateButton(const char *text, std::function<void(hl_ButtonEventArgs)> onclick, hl_AnchorType anchor);
};

#endif //GUISCENE_H
