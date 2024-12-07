//
// Created by openjcd on 27/11/2024.
//

#include "Control.h"
#include <iostream>
#include <ostream>
#include <ranges>

using std::list, std::shared_ptr, std::to_string, std::make_shared;
Control::Control(short w, short h) {
    m_Anchor = ANCHOR_AUTO;
    m_Bounds = Rectangle(0,0,w,h);
    _debug_string = "Control_ANCHOR_AUTO_" + to_string(w) + "_" + to_string(h);
}
Control::Control(short w, short h, const hl_AnchorType anchor) {
    m_Anchor = anchor;
    m_Bounds = Rectangle(0,0,w,h);
    _debug_string = "Control_MANUAL_ANCHOR_" + to_string(w) + "_" + to_string(h);
}
Control::Control(hl_AnchorType anchor) {
    m_Anchor = anchor;
    _debug_string = "Control_" + to_string(anchor) + "_autoSized";
}

Control::Control() {
    m_Anchor = ANCHOR_AUTO;
    _debug_string = "Control_ANCHOR_AUTO_autoSized";
}
Control* Control::SetAnchor(hl_AnchorType anchor) {
    m_Anchor = anchor;
    return this;
}

void Control :: Update(float gameTime) {}
void Control :: UpdatePos() {

    m_Bounds.x = 0;
    m_Bounds.y = 0;
    m_DragBounds = m_DragZone;
    if (m_Parent != nullptr) {
        if (m_StyleProperties.fill_parent_h) {
            m_LocalPosition.y = m_StyleProperties.padding.y;
            m_Bounds.height = m_Parent->m_Bounds.height - m_LocalPosition.y*2;
        }
        if (m_StyleProperties.fill_parent_w) {
            m_LocalPosition.x = m_StyleProperties.padding.x;
            m_Bounds.width = m_Parent->m_Bounds.width - m_LocalPosition.x*2;
        }
        m_Bounds.x = m_Parent->m_Bounds.x + m_LocalPosition.x;
        m_Bounds.y = m_Parent->m_Bounds.y + m_LocalPosition.y;
    } else {
        m_Bounds = Rectangle {0,0,(float)GetRenderWidth(),(float)GetRenderHeight()};
    }
    m_DragBounds.x += m_Bounds.x;
    m_DragBounds.y += m_Bounds.y;
    if (IsWindowResized() && m_Parent == nullptr) { // check this frame if window was resized. if it was, update the anchors of every element.
        BaseLayout();
    }
}

void Control::BaseDraw() {
    if (!IsEnabled) return;
    Draw();
    for (auto &element: m_Children) {
        element->BaseDraw();
    }
    if (_wasHovered && !m_Tooltip.empty()) {
        Vector2 tooltipSize = MeasureTextEx(m_tooltipFont, m_Tooltip.c_str(), m_StyleProperties.font_size, 1);
        DrawRectangle(GetMouseX(), GetMouseY(), tooltipSize.x + 5, tooltipSize.y+5,
            ColorAlpha(m_StyleProperties.background_color, 255.0f));
        DrawTextEx(m_tooltipFont, m_Tooltip.c_str(), (Vector2){GetMouseX()+5.0f, GetMouseY()+5.0f}, m_StyleProperties.font_size, 1, m_StyleProperties.foreground_color);
    }
    PostDraw();
}
void Control::BaseUpdate(float gameTime) {
    UpdatePos();
    if (m_Parent != nullptr) {
        m_StyleProperties.opacity = 1;
        m_StyleProperties.opacity *= m_Parent->GetStyleProperties().opacity;
        m_StyleProperties.background_color.a *= m_StyleProperties.opacity;
        m_StyleProperties.border_color.a *= m_StyleProperties.opacity;
        m_StyleProperties.foreground_color.a *= m_StyleProperties.opacity;
    }
    if (!IsEnabled || !IsActive) return;
    if (IsDragged) {
        m_LocalPosition.x += GetMouseDelta().x;
        m_LocalPosition.y += GetMouseDelta().y;
    }
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
    for (auto &element: m_Children) {
        element->BaseUpdate(gameTime);
    }

    _wasHovered = IsHovered;
    IsHovered = false;
    IsClicked = false; //reset flags at the end of update loop
}

bool Control::CheckMouse(Vector2 mousePos) {
    if (!IsEnabled || !IsActive) return false;
    if (CheckCollisionPointRec(mousePos, m_Bounds)) {
        if (CheckCollisionPointRec(mousePos, m_DragBounds)) {
            IsHovered=true;
            return true;
        }
        if (m_Children.empty()) {
            IsHovered = true;
        } else {
            for (auto &control : std::ranges::reverse_view(m_Children))
            {
                // 'CaptureMouse' flag allows for some widgets to let their parent remain hovered when they would normally
                // capture the mouse hover.
                if (CheckCollisionPointRec(mousePos, control->m_Bounds) && control->CaptureMouse) {
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
        OnClick(hl_ButtonEventArgs(mask, button, this));
    }
}

// chain properties
Control* Control::Add (shared_ptr<Control> child) {
    m_Children.push_back(child);
    child->m_Parent = this;
    BaseLayout();
    return this;
}
Control* Control:: Remove(shared_ptr<Control> child) {
    m_Children.remove(child);
    return this;
}

void Control::Draw() {
    if (m_Parent == nullptr) { return; }
    if (m_StyleProperties.rounding > 0.0f) {
        DrawRectangleRounded(
            Rectangle(m_Bounds.x, m_Bounds.y, m_Bounds.width + 1, m_Bounds.height + 1),
            m_StyleProperties.rounding,
            10,
            m_StyleProperties.background_color);
        DrawRectangleRoundedLinesEx(m_Bounds,
            m_StyleProperties.rounding,
            10,
            m_StyleProperties.border_thickness,
            m_StyleProperties.border_color);
    } else {
        DrawRectangle(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Bounds.height, m_StyleProperties.background_color);
        DrawRectangleLinesEx(m_Bounds, m_StyleProperties.border_thickness, m_StyleProperties.border_color);
    }
}

void Control::PostDraw() { }

Control::~Control() {
    m_Children.clear();
}

Control * Control :: SetStyle(hl_StyleProperties style) {
    m_StyleProperties = style;
    return this;
}

Control * Control::Enable() {
    IsEnabled = true;
    return this;
}

Control * Control::Disable() {
    IsEnabled = false;
    return this;
}

Control * Control::SetRounding(float rounding) {
    m_StyleProperties.rounding = rounding;
    return this;
}

Control * Control:: SetBorderColor(Color color) {
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
    BaseLayout();
    return this;
}

Control * Control::SetSize(float w, float h) {
    SetHeight(h);
    SetWidth(w);
    return this;
}
Control * Control::SetLocalPos(int x, int y) {
    m_LocalPosition = Vector2(x, y);
    return this;
}
Control * Control::FillParentWidth() {
    m_StyleProperties.fill_parent_w = true;
    return this;
}

Control * Control::FillParentHeight() {
    m_StyleProperties.fill_parent_h = true;
    return this;
}

Control *Control::SetWidth(float width) {
    m_Bounds.width = width;
    BaseLayout();
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
Control *Control::EnableDragging() {
    m_DragZone = m_Bounds;
    return this;
}
Control *Control::SetMargin(int horizontal, int vertical) {
    m_StyleProperties.margin = Vector2(horizontal, vertical);
    return this;
}

Control * Control::SetClickAction(std::function<void(hl_ButtonEventArgs)> func){
    OnClick = func;
    GUI_LOG("Set click action for " + _debug_string);
    return this;
}

Control * Control::SetLayoutDirection(hl_GuiLayoutType type) {
    m_layoutType = type;
    BaseLayout();
    return this;
}

Control * Control::SetTooltip(const char *tip) {
    m_Tooltip = tip;
    return this;
}

Control * Control::SetTag(const char *tag) {
    m_Tag = tag;
    return this;
}

Control * Control::DisableMouseCapture() {
    CaptureMouse = false;
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

hl_AnchorType Control::GetAnchor() const {
    return m_Anchor;
}

string Control::GetTag() const {
    return m_Tag;
}

Control * Control::SetMargin(short x, short y) {
    m_StyleProperties.margin = Vector2(x, y);
    return this;
}

Control* Control::Deactivate() {
    m_StyleProperties.opacity = 200.0f;
    m_StyleProperties.background_color.a=200.0f;
    m_StyleProperties.foreground_color.a=200.0f;
    m_StyleProperties.border_color.a= 200.0f;
    IsActive = false;
    return this;
}
Control* Control::Activate() {
    m_StyleProperties.opacity = 1.0f;
    m_StyleProperties.background_color.a=255.0f;
    m_StyleProperties.foreground_color.a=255.0f;
    m_StyleProperties.border_color.a= 255.0f;
    IsActive = true;
    return this;
}
void Control::Layout() {
    hl_LayoutState layout {0,0, m_layoutType};

    std::vector<shared_ptr<Control>> childrenByAnchor[10];
    for (auto &control: m_Children) {
        childrenByAnchor[(int)control->GetAnchor()].emplace_back(control); // sort each child by anchor.
    }

    for (auto &child_auto: childrenByAnchor[9]) {
        if (layout.layout_type == GUI_LAYOUT_HORIZONTAL) {
            layout.cursor_position.x += child_auto->m_StyleProperties.padding.x;
            layout.cursor_position.y  = child_auto->m_StyleProperties.padding.y;
        } else {
            layout.cursor_position.x = child_auto->m_StyleProperties.padding.x;
            layout.cursor_position.y += child_auto->m_StyleProperties.padding.y;
        }
        child_auto->m_LocalPosition = layout.cursor_position;
        if (layout.layout_type == GUI_LAYOUT_HORIZONTAL) {
            layout.cursor_position.x += child_auto->m_Bounds.width;
        } else {
            layout.cursor_position.y += child_auto->m_Bounds.height;
        }
    }
}

void Control::BaseLayout() {
    if (m_Parent != nullptr) {
        switch (m_Anchor) {
            case ANCHOR_TOP_LEFT:
                m_LocalPosition.x = m_StyleProperties.padding.x;
                m_LocalPosition.y = m_StyleProperties.padding.y;
                break;
            case ANCHOR_TOP:
                m_LocalPosition.x = (m_Parent->m_Bounds.width/2 - m_Bounds.width/2);
                m_LocalPosition.y = m_StyleProperties.padding.y;
                break;
            case ANCHOR_TOP_RIGHT:
                m_LocalPosition.x = m_Parent->m_Bounds.width - m_Bounds.width - m_StyleProperties.padding.x;
                m_LocalPosition.y = m_StyleProperties.padding.y;
                break;
            case ANCHOR_LEFT:
                m_LocalPosition.x = m_StyleProperties.padding.x;
                m_LocalPosition.y = (m_Parent->m_Bounds.height/2 - m_Bounds.height/2);
                break;
            case ANCHOR_CENTER:
                m_LocalPosition.x = (m_Parent->m_Bounds.width/2 - m_Bounds.width/2);
                m_LocalPosition.y = (m_Parent->m_Bounds.height/2 - m_Bounds.height/2);
                break;
            case ANCHOR_RIGHT:
                m_LocalPosition.x = (m_Parent->m_Bounds.width - m_Bounds.width - m_StyleProperties.padding.x);
                m_LocalPosition.y = (m_Parent->m_Bounds.height/2 - m_Bounds.height/2);
                break;
            case ANCHOR_BOTTOM_LEFT:
                m_LocalPosition.x = (m_StyleProperties.padding.x);
                m_LocalPosition.y = (m_Parent->m_Bounds.height - m_StyleProperties.padding.y);
                break;
            case ANCHOR_BOTTOM:
                m_LocalPosition.x = (m_Parent->m_Bounds.width/2 - m_Bounds.width/2);
                m_LocalPosition.y = (m_Parent->m_Bounds.height - m_Bounds.height - m_StyleProperties.padding.y);
                break;
            case ANCHOR_BOTTOM_RIGHT:
                m_LocalPosition.x = (m_Parent->m_Bounds.width - m_Bounds.width - m_StyleProperties.padding.x);
                m_LocalPosition.y = (m_Parent->m_Bounds.height - m_Bounds.height - m_StyleProperties.padding.y);
                break;
            case ANCHOR_AUTO:
                break;
        }
    }
    Layout();
    for (auto &child: m_Children) {
        child->BaseLayout();
    }
}