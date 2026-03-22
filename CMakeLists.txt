cmake_minimum_required(VERSION 3.10)

project(GOA_X)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES
    main/main.cpp
    main/UI/menu.cpp
    main/UI/ui_style.cpp
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
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL 
    glfw
)