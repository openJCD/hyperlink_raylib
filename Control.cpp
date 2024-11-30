//
// Created by openjcd on 27/11/2024.
//
#pragma once

#include "Control.h"
#include <iostream>
#include <ostream>
#include <ranges>
#define LOG_WARN(msg) std::cout << msg << std::endl
#define BEGIN_SCISSOR_RECT(rectangle) (BeginScissorMode(rectangle.x, rectangle.y, rectangle.width, rectangle.height))
#define END_SCISSOR_RECT() EndScissorMode()

using namespace std;
using namespace HlGui;

Control::Control(short w, short h, const hl_AnchorType anchor = ANCHOR_TOP_LEFT) {
    m_Anchor = anchor;
    m_Bounds = Rectangle(0,0,w,h);
    m_StyleProperties = hl_StyleProperties(); // default styles
    _debug_string = "Control_" + to_string(anchor) + "_" + to_string(w) + "_" + to_string(h);
}
Control::Control(hl_AnchorType anchor) {
    m_Anchor = anchor;
    m_StyleProperties = hl_StyleProperties(); // default styles
    _debug_string = "Control_" + to_string(anchor) + "_autoSized";
}
Control* Control::SetAnchor(hl_AnchorType anchor) {
    m_Anchor = anchor;
    return this;
}

void Control :: Update(float gameTime) {

}
void Control :: UpdatePos() {

    m_Bounds.x = 0;
    m_Bounds.y = 0;
    m_DragBounds = m_DragZone;
    if (m_Parent != nullptr) {
        m_Bounds.x = m_Parent->m_Bounds.x + m_LocalPosition.x;
        m_Bounds.y = m_Parent->m_Bounds.y + m_LocalPosition.y;
    } else {
        m_Bounds = Rectangle {0,0,(float)GetRenderWidth(),(float)GetRenderHeight()};
    }
    m_DragBounds.x += m_Bounds.x;
    m_DragBounds.y += m_Bounds.y;
    if (IsWindowResized() && m_Parent == nullptr) { // check this frame if window was resized. if it was, update the anchors of every element.
        RecalculateChildrenRecursive();
    }
}
void Control :: BaseDraw() {
    Draw();
    for (auto element: m_Children) {
        element->BaseDraw();
    }
}
void Control::BaseUpdate(float gameTime) {
    UpdatePos();
    if (IsDragged) {
        m_LocalPosition.x += GetMouseDelta().x;
        m_LocalPosition.y += GetMouseDelta().y;
    }
    if (m_Parent == nullptr) CheckMouse(GetMousePosition()); // only recursively check mouse hovers if I am the root control.
    if (IsHovered) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            IsClicked=true;
        }
        else {
            IsClicked=false;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            DoClick(MOUSE_MASK_DOWN, MOUSE_BUTTON_LEFT);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            DoClick(MOUSE_MASK_DOWN, MOUSE_BUTTON_RIGHT);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            DoClick(MOUSE_MASK_UP, MOUSE_BUTTON_LEFT);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            DoClick(MOUSE_MASK_UP, MOUSE_BUTTON_RIGHT);
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        IsDragged=false; //reset drag if the mouse is released at all.
    }
    Update(gameTime);
    for (auto element: m_Children) {
        element->BaseUpdate(gameTime);
    }
    IsHovered = false;
    IsClicked = false; //reset flags at the end of update loop
}

bool Control::CheckMouse(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, m_Bounds)) {
        if (CheckCollisionPointRec(mousePos, m_DragBounds)) {
            IsHovered=true;
            return true;
        }
        if (m_Children.empty()) {
            IsHovered = true;
        } else {
            for (auto control : std::ranges::reverse_view(m_Children))
            {
                if (CheckCollisionPointRec(mousePos, control->m_Bounds)) {
                    control->CheckMouse(mousePos);
                    IsHovered = false;
                    return false;
                }
                IsHovered = true;
            }
        }
    }
    return IsHovered;
}

void Control::DoClick(MouseMask mask, MouseButton button) {
    if (mask == MOUSE_MASK_DOWN) {
        if (button == MOUSE_BUTTON_LEFT) {
            if (IsHovered && CheckCollisionPointRec(GetMousePosition(), m_DragBounds)) {
                IsDragged = true;
                return;
            }
        }
    } else if (mask == MOUSE_MASK_UP) {
        if (button == MOUSE_BUTTON_LEFT) {
            if (IsDragged) {
                IsDragged = false;
                return;
            }
        }
    }
    if (OnClick != nullptr) {
        OnClick(hl_ClickEventArgs(mask, button, this));
    }
}

// chain properties
Control* Control::Add(Control *child) {
    m_Children.push_back(child);
    child->m_Parent = this;
    PlaceChild(child);
    return this;
}
Control* Control:: Remove(Control* child) {
    m_Children.remove(child);
    return this;
}

void Control::Draw() {
    DrawRectangleRounded(m_Bounds, m_StyleProperties.rounding, 10, m_StyleProperties.background_color);
    DrawRectangleRoundedLinesEx(m_Bounds, m_StyleProperties.rounding, 10, m_StyleProperties.border_thickness, m_StyleProperties.border_color);
}

Control::~Control() {
    m_Children.clear();
}

Control* Control :: SetStyle(hl_StyleProperties style) {
    m_StyleProperties = style;
    return this;
}
Control *Control::SetRounding(float rounding) {
    m_StyleProperties.rounding = rounding;
    return this;
}
Control *Control:: SetBorderColor(Color color) {
    m_StyleProperties.border_color = color;
    return this;
}
Control * Control::SetBackgroundColor(Color color) {
    m_StyleProperties.background_color = color;
    return this;
}
Control * Control::SetColor(Color color) {
    m_StyleProperties.foreground_color = color;
    return this;
}

Control *Control::SetHeight(float height) {
    m_Bounds.height = height;
    RecalculateChildrenRecursive();
    return this;
}

Control * Control::SetSize(float w, float h) {
    SetHeight(h);
    SetWidth(w);
    return this;
}

Control *Control::SetWidth(float width) {
    m_Bounds.width = width;
    RecalculateChildrenRecursive();
    return this;
}
Control *Control::SetPadding(short horizontal, short vertical) {
    m_StyleProperties.padding.x = horizontal;
    m_StyleProperties.padding.y = vertical;
    return this;
}

Control * Control::SetPaddingX(short pad) {
    m_StyleProperties.padding.x = pad;
    return this;
}

Control * Control::SetPaddingY(short pad) {
    m_StyleProperties.padding.y = pad;
    return this;
}

Control* Control::SetBorderThickness(__int8 anchor) {
    m_StyleProperties.border_thickness = anchor;
    return this;
}
Control *Control::EnableDragging(Rectangle localDragZone) {
    m_DragZone = localDragZone;
    return this;
}
Control *Control::SetMargin(int horizontal, int vertical) {
    m_StyleProperties.margin = Vector2(horizontal, vertical);
    return this;
}

Control * Control::SetClickAction(void(*func)(hl_ClickEventArgs)) {
    OnClick = func;
    LOG("Set click action for " + _debug_string);
    return this;
}

string Control::GetDebugString() {
    return _debug_string;
}

Rectangle Control::GetBounds() const {
    return m_Bounds;
}

hl_StyleProperties Control::GetStyleProperties() const {
    return m_StyleProperties;
}

//end chain properties
void Control::RecalculateChildrenRecursive() {
    for (auto control: m_Children ) {
        PlaceChild(control);
        control->RecalculateChildrenRecursive();
    }
}

void Control::PlaceChild(Control *child) const {
    float child_w = child->m_Bounds.width;
    float child_h = child->m_Bounds.height;
    LOG("Calculating anchors of "+child->_debug_string);
    switch (child->m_Anchor)  {
        case ANCHOR_TOP_LEFT:
            child->m_LocalPosition.x = child->m_StyleProperties.padding.x;
            child->m_LocalPosition.y = child->m_StyleProperties.padding.y;
            break;
        case ANCHOR_TOP_RIGHT:
            child->m_LocalPosition.x = m_Bounds.width-child->m_StyleProperties.padding.x - child_w;
            child->m_LocalPosition.y = child->m_StyleProperties.padding.y;
        break;
        case ANCHOR_BOTTOM_LEFT:
            child->m_LocalPosition.x = child->m_StyleProperties.padding.x;
            child->m_LocalPosition.y = m_Bounds.height - child->m_StyleProperties.padding.y - child_h;
            break;
        case ANCHOR_BOTTOM_RIGHT:
            child->m_LocalPosition.x = m_Bounds.width - child->m_StyleProperties.padding.x - child_w;
            child->m_LocalPosition.y = m_Bounds.height - child->m_StyleProperties.padding.y - child_h;
            break;
        case ANCHOR_LEFT:
            child->m_LocalPosition.x = child->m_StyleProperties.padding.x;
            child->m_LocalPosition.y = m_Bounds.height / 2 - child_h / 2;
            break;
        case ANCHOR_RIGHT:
            child->m_LocalPosition.x = m_Bounds.width - child->m_StyleProperties.padding.x - child_w;
            child->m_LocalPosition.y = m_Bounds.height / 2 - child_h / 2;
            break;
        case ANCHOR_TOP:
            child->m_LocalPosition.x = m_Bounds.width / 2 - child_w / 2;
            child->m_LocalPosition.y = child->m_StyleProperties.padding.y;
            break;
        case ANCHOR_BOTTOM:
            child->m_LocalPosition.x = m_Bounds.width / 2 - child_w / 2;
            child->m_LocalPosition.y = m_Bounds.height - child->m_StyleProperties.padding.y - child_h;
            break;
        case ANCHOR_CENTER:
            child->m_LocalPosition.x = m_Bounds.width / 2 - child_w / 2;
            child->m_LocalPosition.y = m_Bounds.height / 2 - child_h / 2;
            break;
        default:
            break;           child->m_LocalPosition.y = child->m_StyleProperties.padding.y;

    }
}