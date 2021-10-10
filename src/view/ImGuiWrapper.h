//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_IMGUIWRAPPER_H
#define OPENGL_RENDERER_IMGUIWRAPPER_H
#include <view/GLFWWrapper.h>
#include <view/OpenGLWrapper.h>
#include <imgui.h>

namespace View {
    class ImGuiWrapper {
        private:
            GLFWWrapper* glfwWrapper;
            OpenGLWrapper* openGlWrapper;
            void ShowTextureSettings(bool* p_open);
            void ShowExampleAppSimpleOverlay(bool* p_open);
            void ShowTransformSettings(bool* p_open);
            void HelpMarker(const char* desc);
            bool showTransformSettings = false;
            bool showTextureSettings = false;
            bool showExampleAppSimpleOverlay = true;
        public:
            ImGuiWrapper(GLFWWrapper* glfwWrapper, OpenGLWrapper* openGlWrapper);
            bool WantCaptureMouse();
            bool WantCaptureKeyboard();
            void Init();
            void RenderImGui();
            void Cleanup();

        void ShowMainMenuBar();
    };
}

#endif //OPENGL_RENDERER_IMGUIWRAPPER_H
