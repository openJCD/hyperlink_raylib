//
// Created by openjcd on 30/11/2024.
//

#include "ResourceManager.h"

Font & ResourceManager::GetFont(const char *name) {
    return Fonts[name];
}

Font & ResourceManager::DefaultFont() {
    if (!Fonts.contains("default"))
        Fonts["default"] = GetFontDefault();
    return Fonts["default"];
}

void ResourceManager::RemoveFont(const char *name) {
    Fonts.erase(name);
}
Shader & ResourceManager::GetShader(const char *name) {
    return Shaders[name];
}
void ResourceManager::AddShader(const char *name, Shader shader) {
    Shaders[name] = shader;
}
void ResourceManager::LoadShaderAndAdd(const char *name, const char *path) {
    Shaders[name] = LoadShader(0, path);
}

void ResourceManager::RemoveShader(const char *name) {
    Shaders.erase(name);
}

void ResourceManager::AddFont(const char *name, Font font) {
    Fonts[name] = font;
}
void ResourceManager::LoadFontAndAdd(const char *name, const char *path, short fontSize) {
    Fonts[name] = LoadFontEx(path, fontSize, NULL, NULL);
}
