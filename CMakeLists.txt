cmake_minimum_required(VERSION 3.11)
project(hyperlink_raylib_rebuild)

set(CMAKE_CXX_STANDARD 20)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

#set(raylib_VERBOSE 1)
# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
add_executable(${PROJECT_NAME} main.cpp
        src/hlgui/Control.cpp
        src/hlgui/Control.h
        src/hlgame/game_structs.h
        src/hlgui/gui_structs.h
        src/hlgui/TextLabel.cpp
        src/hlgui/TextLabel.h
        src/hlgui/WindowControl.cpp
        src/hlgui/WindowControl.h
        src/hlgui/ResourceManager.cpp
        src/hlgui/ResourceManager.h
        src/hlgui/hlgui.h
        src/hlgui/Button.cpp
        src/hlgui/Button.h
        src/hlgui/FpsWidget.h
        src/hlgame/NetworkNode.h
        src/hlgame/NetworkNode.cpp
        src/hlgui/perf_profile_helpers.h
        src/hlgame/GameNodeMap.cpp
        src/hlgame/GameNodeMap.h
        src/hlgame/os/CcOS.cpp
        src/hlgame/os/CcOS.h
        src/hlgame/os/OsProgram.cpp
        src/hlgame/os/OsProgram.h
        src/hlgui/GuiScene.cpp
        src/hlgui/GuiScene.h
        src/hlgame/os/MarketplaceApp.cpp
        src/hlgame/os/MarketplaceApp.h
        src/hlgui/ListBox.cpp
        src/hlgui/ListBox.h
        src/hlgame/os/TerminalApp.cpp
        src/hlgame/os/TerminalApp.h
        src/hlgui/LargeTextBox.cpp
        src/hlgui/LargeTextBox.h
        src/hlgui/TextInput.cpp
        src/hlgui/TextInput.h
        tracy/public/TracyClient.cpp
        src/hlgui/ScrollPanel.cpp
        src/hlgui/ScrollPanel.h
        src/program.h
        src/hlgame/os/OsGuiProgram.cpp
        src/hlgame/os/OsGuiProgram.h
        src/hlgui/Orbital3DBackgroundControl.cpp
        src/hlgui/Orbital3DBackgroundControl.h
        src/hlgame/NodeFileSystem.cpp
        src/hlgame/NodeFileSystem.h
)
# copy resources directory to build directory
add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
target_link_libraries(${PROJECT_NAME} raylib -static -static-libgcc -static-libstdc++)
target_compile_options(${PROJECT_NAME} PUBLIC -march=native)