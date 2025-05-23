cmake_minimum_required(VERSION 3.30)
project(synth)

set(CMAKE_CXX_STANDARD 23)

include_directories("libraries/imgui/backends"
        "libraries/imgui"
        "libraries/sdl/include"
)

add_executable(synth main.cpp
        ./libraries/imgui/imgui.cpp
        ./libraries/imgui/imgui_demo.cpp
        ./libraries/imgui/imgui_draw.cpp
        ./libraries/imgui/imgui_widgets.cpp
        ./libraries/imgui/imgui_tables.cpp
        ./libraries/imgui/backends/imgui_impl_sdl3.cpp
        ./libraries/imgui/backends/imgui_impl_sdlrenderer3.cpp
        view/MainWindow.cpp
        view/MainWindow.h)


if (APPLE)
    set(CMAKE_INSTALL_RPATH
            "${CMAKE_SOURCE_DIR}/../libraries/sdl/lib/macos/SDL3.framework")
    target_link_libraries(synth PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/macos/SDL3.framework"
            "-framework CoreFoundation")
elseif (WIN32)
    target_link_libraries(synth PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
    )
    # post-build command to copy the DLLs
    add_custom_command(TARGET synth POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
            "$<TARGET_FILE_DIR:synth>"
    )
elseif (UNIX)
    target_link_libraries(simple_synth PRIVATE
            "-ldl"
            "-ljack"
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/linux-x86_64/libSDL3.a"
    )
endif ()
