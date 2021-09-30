//
// Created by Felix on 24/09/2021.
//

#include "GLFWWrapper.h"
#include <iostream>
#include <excpetions/GLFWException.h>
#include <view/OpenGLWrapper.h>

using namespace View;

void GLFWWrapper::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}
void GLFWWrapper::CreateWindow() {
    window = glfwCreateWindow(ScreenWidth, ScreenHeight, "OpenGLWrapper Renderer", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw (Exception::GLFWException("Failed to create GLFW window"));
    }
    glfwMakeContextCurrent(window);
    // this needs some thoughts about callbacks
    glfwSetFramebufferSizeCallback(window, &OpenGLWrapper::FramebufferSizeCallback);
}

void GLFWWrapper::TerminateWindow() {
    glfwTerminate();
}

GLFWwindow* GLFWWrapper::GetWindow() {
    return window;
}

bool GLFWWrapper::ShouldWindowClose() {
    return glfwWindowShouldClose(window);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void GLFWWrapper::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void GLFWWrapper::SwapBuffersAndPollIOEvents() {
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

glm::vec2 GLFWWrapper::GetScreenDimensions() {
    return glm::vec2(this->ScreenWidth, this->ScreenHeight);
}

void GLFWWrapper::Cleanup(){
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}
