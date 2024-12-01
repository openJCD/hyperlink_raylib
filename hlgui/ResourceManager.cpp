//
// Created by openjcd on 30/11/2024.
//

#include "ResourceManager.h"

Font & ResourceManager::GetFont(const char *name) {
    return res_Fonts[name];
}

Font & ResourceManager::GetDefaultFont() {
    if (!res_Fonts.contains("default"))
        res_Fonts["default"] = GetFontDefault();
    return res_Fonts["default"];
}

void ResourceManager::RemoveFont(const char *name) {
    res_Fonts.erase(name);
}
Shader & ResourceManager::GetShader(const char *name) {
    return res_Shaders[name];
}
void ResourceManager::AddShader(const char *name, Shader shader) {
    res_Shaders[name] = shader;
}
void ResourceManager::LoadShaderAndAdd(const char *name, const char *path) {
    res_Shaders[name] = LoadShader(0, path);
}

void ResourceManager::RemoveShader(const char *name) {
    res_Shaders.erase(name);
}

void ResourceManager::AddFont(const char *name, Font font) {
    res_Fonts[name] = font;
}
void ResourceManager::LoadFontAndAdd(const char *name, const char *path, short fontSize) {
    res_Fonts[name] = LoadFontEx(path, fontSize, NULL, NULL);
}
