//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_OPENGLWRAPPER_H
#define OPENGL_RENDERER_OPENGLWRAPPER_H
#include <view/GLFWWrapper.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace View {
    class OpenGLWrapper {
        public:
            OpenGLWrapper(GLFWWrapper* glfwWrapper);
            void Init();
            void BuildAndCompileShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
            void SetupVerticeData(std::vector<float> vertices);
            void LoadAndCreateTextures(std::string texturePaths[]);
            void CreateTransformations();
            static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
            void ClearCanvas();
            glm::vec4 GetClearColor();
            void Cleanup();

        void Draw();

    private:
            GLFWWrapper* glfwWrapper;
            glm::vec4 ClearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
            unsigned int VBO, VAO;
    };
}

#endif //OPENGL_RENDERER_OPENGLWRAPPER_H
