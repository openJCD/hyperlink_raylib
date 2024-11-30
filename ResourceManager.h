//
// Created by openjcd on 30/11/2024.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>

#include <raylib.h>
using namespace std;

/// static class that has ownership over large resources, like fonts, etc.
class ResourceManager {
private:
    map<string, Font> Fonts = map<string, Font>();
    map<string, Shader> Shaders = map<string, Shader>();
public:
    /// initialise members. won't work without this...
    //for fonts
    Font& GetFont (const char* name);
    Font& DefaultFont();
    void AddFont(const char* name, Font font);
    void LoadFontAndAdd(const char *name, const char *path, short fontSize);
    void RemoveFont(const char* name);

    //for shaders
    Shader& GetShader(const char* name);
    void AddShader(const char* name, Shader shader);
    void LoadShaderAndAdd(const char *name, const char *path);
    void RemoveShader(const char* name);

};



#endif //RESOURCEMANAGER_H
