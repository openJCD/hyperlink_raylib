//
// Created by openjcd on 30/11/2024.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>
#include <raylib.h>
using std::map;
using std::string;

static map<string, Font> res_Fonts = map<string, Font>();
static map<string, Shader> res_Shaders = map<string, Shader>();
/// static class that has ownership over large resources, like fonts, etc.
class ResourceManager {
private:
public:
    //for fonts
    static Font& GetFont (const char* name);
    static Font& GetDefaultFont();
    static void AddFont(const char* name, Font font);

    static void LoadFontAndAdd(const char *name, const char *path, short fontSize);
    static void RemoveFont(const char* name);

    //for shaders
    static Shader& GetShader(const char* name);
    static void AddShader(const char* name, Shader shader);
    static void LoadShaderAndAdd(const char *name, const char *path);
    static void RemoveShader(const char* name);

};



#endif //RESOURCEMANAGER_H
