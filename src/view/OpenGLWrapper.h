//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_OPENGLWRAPPER_H
#define OPENGL_RENDERER_OPENGLWRAPPER_H
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace View
{
    class GLFWWrapper;
}

struct GLFWwindow;

namespace View {
    class OpenGLWrapper {
        public:
            OpenGLWrapper(View::GLFWWrapper* glfwWrapper);
            void Init();
            static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
            void ClearCanvas();
            glm::vec4 GetClearColor();

    private:
            GLFWWrapper* glfwWrapper;
            glm::vec4 ClearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    };
}

#endif //OPENGL_RENDERER_OPENGLWRAPPER_H
