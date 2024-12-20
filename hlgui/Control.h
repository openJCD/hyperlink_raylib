﻿//
// Created by openjcd on 27/11/2024.
//
#pragma once
#include <functional>
#include <list>
#include <memory>
#include <raylib.h>
#include <string>

#include "ResourceManager.h"
#include "gui_structs.h"
#ifndef CONTROL_H
#define CONTROL_H
using std::list;
using std::shared_ptr;
/// The root of the GUI hierarchy. Provides methods for styling, click functions, etc.
class Control {
protected:
    string _debug_string = "Control";

    Rectangle m_Bounds{0,0,0,0};
    /// the user-defined local draggable rectangle area.
    Rectangle m_DragZone{0,0,0,0};
    /// the bounds to check the actual drag against.
    Rectangle m_DragBounds{0,0,0,0};

    Vector2 m_LocalPosition{0,0};

    hl_AnchorType m_Anchor = ANCHOR_TOP_LEFT;
    hl_StyleProperties m_StyleProperties = ResourceManager::GetDefaultStyle();
    list<shared_ptr<Control>> m_Children;
    Control* m_Parent = nullptr;

    bool IsHovered = false;
    bool _wasHovered = false;
    bool IsClicked = false;
    bool IsDragged = false;
    bool IsEnabled = true;
    void UpdatePos();

    virtual void DoClick(MouseMask mask, MouseButton button);
    std::function<void(hl_ButtonEventArgs)> OnClick = nullptr;

    virtual void Draw();
    virtual void Update(float gameTime);
    void         PlaceChild(shared_ptr<Control> child) const;
    void         RecalculateChildrenRecursive() const;
    virtual void RecalculateBounds();
public:
    virtual  ~Control();

    /*ctor*/ Control(short w, short h, hl_AnchorType anchor);
    explicit Control(hl_AnchorType anchor);
    /// When I am hovered, check through children to see which is under mouse hover.
    /// Returns true if root is hovered, false if the rest of the UI is hovered.
    /// Use to block clicks to the game world in main loop.
    bool CheckMouse(Vector2 mousePos);
    /// Draw the control. Must be called between BeginDrawing and EndDrawing.
    /// Must be called on the root Control.
    void BaseDraw();
    /// Update the root Control's position, along with all children and so on.
    void     BaseUpdate(float gameTime);
    Control* SetAnchor(hl_AnchorType anchor);
    virtual Control* Add(shared_ptr<Control> child);
    Control* Remove(shared_ptr<Control> child);
    virtual Control* SetStyle(hl_StyleProperties style);
    Control* Enable();
    Control* Disable();
    Control* SetRounding(float rounding);
    Control* SetWidth(float width);
    Control* SetHeight(float height);
    Control* SetSize(float w, float h);
    Control* FillParentWidth();
    Control* FillParentHeight();
    Control* SetBorderColor(Color color);
    Control* SetBackgroundColor(Color color);
    Control* SetColor(Color color);
    Control* SetPadding(short horizontal, short vertical);
    Control* SetPaddingX(short pad);
    Control* SetPaddingY(short pad);
    Control* SetOpacity(float opacity);
    Control* SetMargin(short x, short y);
    Control* SetBorderThickness(__int8 thickness);
    /// Allow the user to drag this element around.
    /// Set the draggable area to the whole UI element.
    Control* EnableDragging();
    /// Allow the user to drag this element around.
    /// Must specify the draggable area.
    Control* EnableDragging(Rectangle localDragZone);
    Control* SetMargin(int horizontal, int vertical);
    Control* SetClickAction(std::function<void(hl_ButtonEventArgs)> func);

    [[nodiscard]] string   GetDebugString();
    [[nodiscard]] Rectangle GetBounds() const;
    [[nodiscard]] hl_StyleProperties GetStyleProperties() const;
    [[nodiscard]] hl_AnchorType GetAnchor() const;
};

inline Control * Control::SetOpacity(float opacity) {
    m_StyleProperties.opacity = opacity;
    return this;
}

#endif //CONTROL_H
