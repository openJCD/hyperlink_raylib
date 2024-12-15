//
// Created by openjcd on 30/11/2024.
//

#include "ResourceManager.h"

Font & ResourceManager::GetFont(const char *name) {
    if (!res_Fonts.contains(name)) {
        return GetDefaultFont();
    } else {
        return res_Fonts[name];
    }
}

Font & ResourceManager::GetDefaultFont() {
    if (!res_Fonts.contains("default"))
        res_Fonts["default"] = GetFontDefault();
    return res_Fonts["default"];
}

void ResourceManager::RemoveFont(const char *name) {
    res_Fonts.erase(name);
}

void ResourceManager:: AddStyle(const char *name, hl_StyleProperties style) {
    res_StylePresets[name] = style;
}

void ResourceManager::SetDefaultStyle(hl_StyleProperties style) {
    res_StylePresets["default"] = style;
}

hl_StyleProperties ResourceManager::GetDefaultStyle() {
    if (!res_StylePresets.contains("default")) {
        res_StylePresets["default"] = hl_StyleProperties();
    }
    return res_StylePresets["default"];
}

hl_StyleProperties ResourceManager::GetStyle(const char *name) {
    if (!res_StylePresets.contains(name)) {
        return GetDefaultStyle();
    }
    return res_StylePresets[name];
}

void ResourceManager::AddFont(const char *name, Font font) {
    res_Fonts[name] = font;
    SetTextureFilter(res_Fonts[name].texture, TEXTURE_FILTER_TRILINEAR);
}

void ResourceManager::LoadFontAndAdd(const char *name, const char *path, short fontSize) {
    res_Fonts[name] = LoadFontEx(path, fontSize, NULL, NULL);
    SetTextureFilter(res_Fonts[name].texture, TEXTURE_FILTER_POINT);
}
