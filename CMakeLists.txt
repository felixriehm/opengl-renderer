cmake_minimum_required(VERSION 3.20)
project(opengl_renderer)

set(CMAKE_CXX_STANDARD 14)

# only works under linux
#if (${TARGET_64} MATCHES ON)
#    set(BUILD_ARCH "-m64")
#else ()
#    set(BUILD_ARCH "-m32")
#endif ()

include_directories(include
        include/stb_image
        include/imgui
        src)

link_directories(lib/glew/lib/x64
        lib/glfw/lib/x64)

# for specific target use target_link_libraries(target_name lib_name)
link_libraries(opengl32.lib
        glew32.lib
        glfw3.lib)

file(GLOB SOURCE_FILES src/*.cpp src/view/*.cpp src/shader/*.cpp src/renderer/*.cpp src/texture/*.cpp src/scene/*.cpp src/scene/entity/*.cpp src/user_input/*.cpp src/scene/camera/*.cpp lib/stb_image/src/*.cpp lib/imgui/src/*.cpp)

#add_compile_options(/E ${SOURCE_FILES})

## for console to disappear at start change to add_executable(opengl_renderer WIN32 ${SOURCE_FILES})
add_executable(opengl_renderer ${SOURCE_FILES})


