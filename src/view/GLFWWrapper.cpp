//
// Created by Felix on 24/09/2021.
//

#include "GLFWWrapper.h"
#include <iostream>
#include <excpetions/GLFWException.h>
#include <view/OpenGLWrapper.h>
#include <boost/bind/bind.hpp>

using namespace View;

GLFWWrapper* GLFWWrapper::thisObject = nullptr;

void GLFWWrapper::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    onKeyPressed = new boost::signals2::signal<void (int, float)>;
    onMouseButton = new boost::signals2::signal<void (int, int, int)>;
    onMouseChanged = new boost::signals2::signal<void (double, double)>;
    onMouseScrollChanged = new boost::signals2::signal<void (double, double)>;

    thisObject = this;
}

void GLFWWrapper::CreateWindow() {
    window = glfwCreateWindow(ScreenWidth, ScreenHeight, "OpenGL Renderer", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw (Exception::GLFWException("Failed to create GLFW window"));
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &OpenGLWrapper::FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    ShowCursor(true);
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

bool GLFWWrapper::IsCursorShown(){
    return isCursorShown;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void GLFWWrapper::ProcessInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_ESCAPE, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_D, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_E, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        (*onKeyPressed)(GLFW_KEY_Q, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void GLFWWrapper::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    (*thisObject->onMouseChanged)(xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GLFWWrapper::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    (*thisObject->onMouseScrollChanged)(xoffset, yoffset);
}

void GLFWWrapper::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        (*thisObject->onMouseButton)(button, action, mods);
}

void GLFWWrapper::ShowCursor(bool show){
    show ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    isCursorShown = show;
}

void GLFWWrapper::WindowShouldClose(){
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

boost::signals2::signal<void (int, float)>* GLFWWrapper::OnKeyPressed() {
    return onKeyPressed;
}

boost::signals2::signal<void (int, int, int)>* GLFWWrapper::OnMouseButton() {
    return onMouseButton;
}

boost::signals2::signal<void (double, double)>* GLFWWrapper::OnMouseChanged(){
    return onMouseChanged;
}

boost::signals2::signal<void (double, double)>* GLFWWrapper::OnMouseScrollChanged(){
    return onMouseScrollChanged;
}

void GLFWWrapper::Cleanup(){
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    onKeyPressed->disconnect_all_slots();
    onMouseButton->disconnect_all_slots();
    onMouseChanged->disconnect_all_slots();
    onMouseScrollChanged->disconnect_all_slots();
    delete(onKeyPressed);
    delete(onMouseButton);
    delete(onMouseChanged);
    delete(onMouseScrollChanged);
    glfwTerminate();
}
