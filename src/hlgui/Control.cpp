//
// Created by openjcd on 27/11/2024.
//

#include "Control.h"
#include <iostream>
#include <ostream>
#include <ranges>
#include <bits/ranges_algo.h>

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
    Redraw = true;
    return this;
}

void Control :: Update(float gameTime) {}
void Control :: UpdatePos() {
    m_DragBounds = m_DragZone;
    if (m_Parent != nullptr) {
        // m_Bounds.x = 0;
        // m_Bounds.y = 0;
        m_Bounds.x = m_Parent->m_Bounds.x + m_LocalPosition.x;
        m_Bounds.y = m_Parent->m_Bounds.y + m_LocalPosition.y;
    } else {
        m_Bounds = Rectangle {0,0,(float)GetRenderWidth(),(float)GetRenderHeight()};
    }
    m_DragBounds.x = m_Bounds.x;
    m_DragBounds.y = m_Bounds.y;
    if (IsWindowResized() && m_Parent == nullptr){
        // check this frame if window was resized. if it was, run the layout again.
        BaseLayout();
        Redraw = true;
    }
}
RenderTexture2D Control::BaseDraw() {
    if (!IsEnabled) {
        BeginTextureMode(m_renderTexture);
        ClearBackground(TRANSPARENT);
        EndTextureMode();
        return m_renderTexture;
    }
    // don't bother drawing if nothing interesting happened.
    // this system leads to needing a lot of assignments to 'Redraw',
    // which is very ugly and a bit of a faff, but the performance save is absolutely worth it.
    if (!Redraw) {
        // Test code to check when the surface isn't being redrawn.
        // BeginTextureMode(m_renderTexture);
        // DrawRectangle(0,0,m_Bounds.width, m_Bounds.height, ColorAlpha(m_StyleProperties.border_color, 100));
        // EndTextureMode();
        return m_renderTexture;
    }
    BeginTextureMode(m_renderTexture);
    ClearBackground(TRANSPARENT);
    Draw();
    EndTextureMode();
    for (auto &element: m_Children) {
        RenderTexture2D childTex = element->BaseDraw();
        BeginTextureMode(m_renderTexture);
        BeginBlendMode(RL_BLEND_ALPHA_PREMULTIPLY); //premultiplied alpha is required for nice font rendering.
        DrawTextureRec(childTex.texture,
    Rectangle( 0, 0, (float)childTex.texture.width, -(float)childTex.texture.height),
    Vector2(element->m_LocalPosition.x,element->m_LocalPosition.y),
        WHITE);
        EndBlendMode();
        EndTextureMode();
    }

    BeginTextureMode(m_renderTexture);
    PostDraw();
    //m_Tooltip = TextFormat("Screen Position: %i, %i Local Position: %i %i", m_Bounds.x, m_Bounds.y, m_LocalPosition.x, m_LocalPosition.y);
    if (_wasHovered && !m_Tooltip.empty()) {
        Vector2 tooltipSize = MeasureTextEx(m_tooltipFont, m_Tooltip.c_str(), m_StyleProperties.font_size, 1);
        DrawRectangle(0, 0, tooltipSize.x + 5, tooltipSize.y+5, m_StyleProperties.background_color);
        DrawTextEx(m_tooltipFont, m_Tooltip.c_str(), (Vector2){5.0f, 5.0f}, m_StyleProperties.font_size, 1, m_StyleProperties.foreground_color);
    }
    EndTextureMode();

    // reset the redraw flag to prevent more unnecessary draw operations.
    // this has the side effect of requiring the UI to be UPDATED BEFORE IT IS DRAWN, as otherwise, the Redraw flag will never be set to true.
    Redraw = false;

    return m_renderTexture;
}
void Control::BaseUpdate(float gameTime) {
    if (m_Parent != nullptr) {
        m_StyleProperties.opacity = 1;
        m_StyleProperties.opacity *= m_Parent->GetStyleProperties().opacity;
        m_StyleProperties.background_color.a *= m_StyleProperties.opacity;
        m_StyleProperties.border_color.a *= m_StyleProperties.opacity;
        m_StyleProperties.foreground_color.a *= m_StyleProperties.opacity;
    }
    UpdatePos();
    if (!IsEnabled || !IsActive) return;
    if (IsDragged) {
        m_LocalPosition.x += GetMouseDelta().x;
        m_LocalPosition.y += GetMouseDelta().y;
        Redraw = true;
    }
    if (IsHovered) {
        Redraw = true;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            IsClicked=true;
            Redraw = true;
        }
        else {
            IsClicked=false;
            Redraw = true;
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
        Redraw = true;
    }
    Update(gameTime);
    for (auto &element: m_Children) {
        element->BaseUpdate(gameTime);
        if (element->Redraw) {    // Redraw myself if any of my children have redraw enabled.
            Redraw=true;          // This is for edge-cases like the user having their mouse cursor outside of the window
        }                         // in which an active text input is contained.
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
            Redraw = true;
            return true;
        }
        if (m_Children.empty()) {
            IsHovered = true;
        } else {
            for (auto &control : std::ranges::reverse_view(m_Children))
            {
                // 'CaptureMouse' flag allows for some widgets to let their parent remain hovered when they would normally
                // capture the mouse hover.
                // Widget must be enabled as well, otherwise 'closed' windows block mouse events that appear as if they should work.
                if (CheckCollisionPointRec(mousePos, control->m_Bounds) && control->CaptureMouse && control->IsEnabled) {
                    control->CheckMouse(mousePos);
                    IsHovered = false;
                    Redraw=true;
                    return false;
                }
                IsHovered = true;
                Redraw=true;
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
Control* Control::Add (shared_ptr<Control> child) {
    m_Children.push_back(child);
    child->m_Parent = this;
    // BaseLayout(); <- Moved this to the 'End' / 'EndControl<T>' call in the GuiScene to avoid unnecessary texture loading at startup.
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
            Rectangle(0, 0, m_Bounds.width + 1, m_Bounds.height + 1),
            m_StyleProperties.rounding,
            10,
            m_StyleProperties.background_color);
    } else {
        DrawRectangle(0, 0, m_Bounds.width, m_Bounds.height, m_StyleProperties.background_color);
    }
}

void Control::PostDraw() {
    if (m_Parent == nullptr) { return; }
    if (m_StyleProperties.rounding > 0.0f) {
        DrawRectangleRoundedLinesEx((Rectangle){0, 0, m_Bounds.width, m_Bounds.height},
        m_StyleProperties.rounding,
        10,
        m_StyleProperties.border_thickness,
        m_StyleProperties.border_color);
    } else {
        DrawRectangleLinesEx((Rectangle){0, 0, m_Bounds.width, m_Bounds.height}, m_StyleProperties.border_thickness, m_StyleProperties.border_color);
    }
}

Control::~Control() {
    m_Children.clear();
}

Control * Control :: SetStyle(hl_StyleProperties style) {
    m_StyleProperties = style;
    Redraw=true;
    return this;
}

Control * Control::Enable() {
    IsEnabled = true;
    Redraw=true;
    return this;
}

Control * Control::Disable() {
    IsEnabled = false;
    Redraw=true;
    return this;
}

Control * Control::SetRounding(float rounding) {
    m_StyleProperties.rounding = rounding;
    Redraw=true;
    return this;
}

Control * Control:: SetBorderColor(Color color) {
    m_StyleProperties.border_color = color;
    Redraw=true;
    return this;
}

Control * Control::SetBackgroundColor(Color color) {
    m_StyleProperties.background_color = color;
    Redraw=true;
    return this;
}

Control * Control::SetColor(Color color) {
    m_StyleProperties.foreground_color = color;
    Redraw=true;
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
    Redraw=true;
    return this;
}

void Control::BringToTop(shared_ptr<Control> control) {
    if (control != nullptr) {
        if (control->m_Parent == this) {
            m_Children.remove(control);
            m_Children.push_back(control);
            Redraw=true;
        }
    }
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

Control * Control::SetClickAction(std::function<void(hl_ClickEventArgs)> func){
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
    m_StyleProperties.opacity = 127.0f;
    m_StyleProperties.background_color.a=127.0f;
    m_StyleProperties.foreground_color.a=127.0f;
    m_StyleProperties.border_color.a= 127.0f;
    IsActive = false;
    Redraw=true;
    return this;
}
Control* Control::Activate() {
    m_StyleProperties.opacity = 1.0f;
    m_StyleProperties.background_color.a=255.0f;
    m_StyleProperties.foreground_color.a=255.0f;
    m_StyleProperties.border_color.a= 255.0f;
    IsActive = true;
    Redraw=true;
    return this;
}
void Control::Layout() {
    hl_LayoutState layout {0,0, m_layoutType};

    std::vector<shared_ptr<Control>> childrenByAnchor[10];
    for (auto &control: m_Children) {
        childrenByAnchor[(int)control->GetAnchor()].emplace_back(control); // sort each child by anchor.
    }

    for (auto &child_auto: childrenByAnchor[9]) {
        if (child_auto->IsFloating) continue;
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
    m_Bounds.width = std::ranges::max(layout.cursor_position.x, m_Bounds.width);
    m_Bounds.height = std::ranges::max(layout.cursor_position.y, m_Bounds.height);
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
    if (m_Parent!=nullptr) {
        if (m_StyleProperties.fill_parent_h) {
            m_LocalPosition.y = m_StyleProperties.padding.y;
            m_Bounds.height = m_Parent->m_Bounds.height - m_LocalPosition.y*2;
            // change this in future to be "fill as much space as possible" rather than "fill all the space".
        }
        if (m_StyleProperties.fill_parent_w) {
            m_LocalPosition.x = m_StyleProperties.padding.x;
            m_Bounds.width = m_Parent->m_Bounds.width - m_LocalPosition.x*2;
        }
    }
    // load render texture again with updated width/height values.
    if (m_renderTexture.texture.width != (int)m_Bounds.width || m_renderTexture.texture.height != (int)m_Bounds.height) {
        UnloadRenderTexture(m_renderTexture);
        m_renderTexture = LoadRenderTexture((int)m_Bounds.width, (int)m_Bounds.height);
    }
    Redraw = true;
    for (auto &child: m_Children) {
        child->BaseLayout();
    }
}