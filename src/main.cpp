#include <windows.h>
#include <view/Gui.h>



int main()
{
    try{
        View::Gui().Run();
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