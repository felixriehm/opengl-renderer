//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_IMGUIWRAPPER_H
#define OPENGL_RENDERER_IMGUIWRAPPER_H
#include <view/GLFWWrapper.h>
#include <view/OpenGLWrapper.h>

namespace View {
    class ImGuiWrapper {
        private:
            GLFWWrapper* glfwWrapper;
            OpenGLWrapper* openGlWrapper;
        public:
            ImGuiWrapper(GLFWWrapper* glfwWrapper, OpenGLWrapper* openGlWrapper);
            void Init();
            void RenderImGui();
            void Cleanup();
        void RenderDrawData();

        void ConfigureImgui();
    };
}

#endif //OPENGL_RENDERER_IMGUIWRAPPER_H
