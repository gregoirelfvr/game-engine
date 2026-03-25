cmake_minimum_required(VERSION 3.10)

project(GOA_X)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Find GLM from homebrew or user local
find_path(GLM_INCLUDE_DIR glm/glm.hpp PATHS /opt/homebrew/include /usr/local/include)
if(NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "GLM not found! Make sure `brew install glm` was run.")
endif()

set(SOURCES
    main/main.cpp
    main/UI/menu.cpp
    main/UI/ui_style.cpp
    main/Engine/Shader.cpp
    main/Engine/SpriteRenderer.cpp
    main/Engine/Camera.cpp
    main/Class/Player.cpp
    main/Class/Character.cpp
    imgui-master/imgui.cpp
    imgui-master/imgui_draw.cpp
    imgui-master/imgui_tables.cpp
    imgui-master/imgui_widgets.cpp
    imgui-master/backends/imgui_impl_glfw.cpp
    imgui-master/backends/imgui_impl_opengl3.cpp
    libs/stb_image_impl.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master/backends
    ${GLM_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL 
    glfw
)