#include <windows.h>

#include <stb_image.h>

#include <shader/shader_m.h>
#include <utility/filesystem.h>
#include <view/Gui.h>

#include <iostream>
#include <cmath>



int main()
{
    try{
        View::Gui();
    } catch (...) {
        return -1;
    }
    return 0;
}

// entry point for WIN32 (without console start). CMAKE: add_executable(opengl_renderer WIN32 ...)
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    main();
}