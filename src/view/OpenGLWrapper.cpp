//
// Created by Felix on 24/09/2021.
//

#include <glew/glew.h>
#include <view/OpenGLWrapper.h>
#include <excpetions/GLEWException.h>
#include <iostream>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace View;

class FileSystem {
public:
    static std::string getPath(const std::string& path);
};

OpenGLWrapper::OpenGLWrapper(GLFWWrapper* glfwWrapper){
    this->glfwWrapper = glfwWrapper;
}

void OpenGLWrapper::Init() {
    // glad: load all OpenGLWrapper function pointers
    // ---------------------------------------
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    // we use glew instead of glad - init glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw (Exception::GLEWException(std::to_string((unsigned short) glewGetErrorString(err)).c_str()));
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWrapper::ClearCanvas() {
    glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
}

glm::vec4 OpenGLWrapper::GetClearColor() {
    return this->ClearColor;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void OpenGLWrapper::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
