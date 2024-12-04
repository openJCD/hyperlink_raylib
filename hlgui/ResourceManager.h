//
// Created by openjcd on 30/11/2024.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>
#include <raylib.h>
#include "gui_structs.h"
using std::map;
using std::string;

static map<string, Font> res_Fonts = map<string, Font>();
static map<string, Shader> res_Shaders = map<string, Shader>();
static map<string, hl_StyleProperties> res_StylePresets = map<string, hl_StyleProperties>();
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
    // styles
    static void AddStyle(const char* name, hl_StyleProperties style);
    static void SetDefaultStyle(hl_StyleProperties style);
    static hl_StyleProperties GetDefaultStyle();
    static hl_StyleProperties GetStyle(const char* name);
};



#endif //RESOURCEMANAGER_H
