//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_OPENGLWRAPPER_H
#define OPENGL_RENDERER_OPENGLWRAPPER_H
#include <view/GLFWWrapper.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <camera/Camera.h>

namespace View {
    class OpenGLWrapper {
        public:
            OpenGLWrapper(View::GLFWWrapper* glfwWrapper, Camera* camera);
            void Init();
            void BuildAndCompileShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
            void SetupVerticeData(std::vector<float> vertices);
            void LoadAndCreateTextures(std::string texturePaths[]);
            void CreateTransformations(float deltaTIme);
            static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
            void ClearCanvas();
            glm::vec4 GetClearColor();
            void Cleanup();
            void Draw();
            void AutoRotateObject(bool rotate);
            void RotateObject(int axis, float angle);
        void TranslateObject(int axis, float position);
        void ScaleObject(int axis, float scale);

        void SetTextureWrapping(int i, int texture = -1);

        void SetTextureFiltering(int i, int texture = -1);

        void ScaleTextCoord(int axis, float scale);
        void SetTextureWrappingBorderColor(float *borderColor);

    private:
            GLFWWrapper* glfwWrapper;
            Camera* camera;
            glm::vec4 ClearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
            unsigned int VBO, VAO;
            unsigned int textures[2] = {};
            bool rotateObject = true;
            glm::mat4 model = glm::mat4(1.0f);
    };
}

#endif //OPENGL_RENDERER_OPENGLWRAPPER_H
