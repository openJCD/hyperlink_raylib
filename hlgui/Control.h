//
// Created by openjcd on 27/11/2024.
//
#pragma once
#include <list>
#include <raylib.h>
#include <string>
#include "structs.cpp"
#ifndef CONTROL_H
#define CONTROL_H
using std::list;
namespace HlGui {

    /// The root of the GUI hierarchy. Provides methods for styling, click functions, etc.
class Control {
private:
protected:
    string _debug_string = "Control";

    Rectangle m_Bounds{0,0,0,0};
    /// the user-defined local draggable rectangle area.
    Rectangle m_DragZone{0,0,0,0};
    /// the bounds to check the actual drag against.
    Rectangle m_DragBounds{0,0,0,0};

    Vector2 m_LocalPosition{0,0};

    hl_AnchorType m_Anchor = ANCHOR_TOP_LEFT;
    hl_StyleProperties m_StyleProperties;

    list<Control*> m_Children;
    Control* m_Parent = nullptr; // this is essential, otherwise the nullptr check fails, and we get undefined behaviour.

    float m_Opacity = 1.0f;
    bool IsHovered = false;
    bool IsClicked = false;
    bool IsDragged = false;
    void UpdatePos();

    virtual void DoClick(MouseMask mask, MouseButton button);
    void (*OnClick)(hl_ClickEventArgs) = nullptr;

    virtual void Draw();
    virtual void Update(float gameTime);
    void     PlaceChild(Control* child) const;
    void     RecalculateChildrenRecursive();
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
    void     BaseDraw();
    /// Update the root Control's position, along with all children and so on.
    void     BaseUpdate(float gameTime);
    Control* SetAnchor(hl_AnchorType anchor);
    virtual Control* Add(Control* child);
    Control* Remove(Control* child);
    Control* SetStyle(hl_StyleProperties style);
    Control* SetRounding(float rounding);
    Control* SetWidth(float width);
    Control* SetHeight(float height);
    Control* SetSize(float w, float h);
    Control* SetBorderColor(Color color);
    Control* SetBackgroundColor(Color color);
    Control* SetColor(Color color);
    Control* SetPadding(short horizontal, short vertical);
    Control* SetPaddingX(short pad);
    Control* SetPaddingY(short pad);
    Control* SetBorderThickness(__int8 thickness);
    /// Allow the user to drag this element around.
    /// Set the draggable area to the whole UI element.
    Control* EnableDragging();
    /// Allow the user to drag this element around.
    /// Must specify the draggable area.
    Control* EnableDragging(Rectangle localDragZone);
    Control* SetMargin(int horizontal, int vertical);
    Control* SetClickAction(void (*func)(hl_ClickEventArgs));

    string   GetDebugString();
    [[nodiscard]] Rectangle GetBounds() const;
    [[nodiscard]] hl_StyleProperties GetStyleProperties() const;
};
}



#endif //CONTROL_H
