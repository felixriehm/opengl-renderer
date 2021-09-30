//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_GLFWWRAPPER_H
#define OPENGL_RENDERER_GLFWWRAPPER_H
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

namespace View {
    class GLFWWrapper {
        public:
            void Init();
            void CreateWindow();
            GLFWwindow* GetWindow();
            void TerminateWindow();
            void ProcessInput();
            bool ShouldWindowClose();
            glm::vec2 GetScreenDimensions();
            void Cleanup();

        void SwapBuffersAndPollIOEvents();

    private:
            // settings
            unsigned int ScreenWidth = 2400;
            unsigned int ScreenHeight = 1400;
            GLFWwindow* window;
    };
}

#endif //OPENGL_RENDERER_GLFWWRAPPER_H
