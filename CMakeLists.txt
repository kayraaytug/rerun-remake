cmake_minimum_required(VERSION 3.14)
project(engine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Define paths
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
set(IMGUI_DIR ${EXTERNAL_DIR}/imgui)
set(RAYLIB_DIR ${EXTERNAL_DIR}/raylib)
set(RLIMGUI_DIR ${EXTERNAL_DIR}/rlImGui)
set(IMGUIFILEDIALOG_DIR ${EXTERNAL_DIR}/ImGuiFileDialog)
find_package(Eigen3 REQUIRED)

# Collect source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Emscripten specific settings
if (EMSCRIPTEN)
    set(PLATFORM "Web" CACHE STRING "Platform to build for" FORCE)
    set(GRAPHICS "OpenGL_ES_3.0" CACHE STRING "Graphics API" FORCE)
    
    # Raylib specific options
    set(BUILD_EXAMPLES OFF CACHE BOOL "Build the examples" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "Build the games" FORCE)
    
    # GLFW options
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" FORCE)
    
    # Remove X11 and Wayland related settings
    unset(USE_WAYLAND CACHE)
    unset(USE_X11 CACHE)
    unset(GLFW_BUILD_X11 CACHE)
    unset(GLFW_BUILD_WAYLAND CACHE)
endif()

# Copy resources (only for desktop builds)
if (NOT EMSCRIPTEN)
    file(COPY ${RESOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
endif()

# Add raylib
add_subdirectory(${RAYLIB_DIR})

# Configure Eigen
include_directories(${EIGEN_DIR})

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}
    ${RLIMGUI_DIR}
    ${IMGUIFILEDIALOG_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

# rlImGui and FileDialog sources
set(RLIMGUI_SOURCES ${RLIMGUI_DIR}/rlImGui.cpp)
set(IMGUIFILEDIALOG_SOURCES ${IMGUIFILEDIALOG_DIR}/ImGuiFileDialog.cpp)

# Add sources
target_sources(${PROJECT_NAME} PRIVATE 
    ${IMGUI_SOURCES} 
    ${RLIMGUI_SOURCES} 
    ${IMGUIFILEDIALOG_SOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib Eigen3::Eigen)

# Emscripten-specific link options
if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE
        "SHELL:-s USE_GLFW=3"
        "SHELL:-s USE_WEBGL2=1"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        "SHELL:-s DEMANGLE_SUPPORT=1"
        "SHELL:-s ASSERTIONS=1"
        "SHELL:-s WASM=1"
        "SHELL:-s NO_EXIT_RUNTIME=1"
        "SHELL:-s ASYNCIFY=1"
        "SHELL:-s FILESYSTEM=1"
        "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/shell.html"
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/resources@/resources"
    )
endif()