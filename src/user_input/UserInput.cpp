//
// Created by Felix on 09/10/2021.
//

#include "UserInput.h"
#include <boost/bind/bind.hpp>
#include <scene/camera/Camera.h>
#include <view/ImGuiWrapper.h>
#include <view/GLFWWrapper.h>
#include <glfw/glfw3.h>

using namespace boost::placeholders;

UserInput::UserInput(View::GLFWWrapper* glfwWrapper, Camera* camera, View::ImGuiWrapper* imGuiWrapper){
    this->glfwWrapper = glfwWrapper;
    this->camera = camera;
    this->imGuiWrapper = imGuiWrapper;
}

void UserInput::Init(){
    glfwWrapper->OnKeyPressed()->connect(boost::bind(&UserInput::OnKeyPressed, this, _1, _2));
    glfwWrapper->OnMouseButton()->connect(boost::bind(&UserInput::OnMouseButton, this, _1, _2, _3));
    glfwWrapper->OnMouseChanged()->connect(boost::bind(&UserInput::OnMouseChanged, this, _1, _2));
    glfwWrapper->OnMouseScrollChanged()->connect(boost::bind(&UserInput::OnMouseScrollChanged, this, _1, _2));
    lastY = glfwWrapper->GetScreenDimensions().x / 2.0f;
    lastY = glfwWrapper->GetScreenDimensions().y / 2.0f;
}

void UserInput::OnKeyPressed(int key, float deltaTime) {
    if(cameraMode){
        switch (key) {
            case GLFW_KEY_W:
                camera->ProcessMovement(FORWARD, deltaTime);
                break;
            case GLFW_KEY_S:
                camera->ProcessMovement(BACKWARD, deltaTime);
                break;
            case GLFW_KEY_A:
                camera->ProcessMovement(LEFT, deltaTime);
                break;
            case GLFW_KEY_D:
                camera->ProcessMovement(RIGHT, deltaTime);
                break;
            case GLFW_KEY_E:
                camera->ProcessMovement(UP, deltaTime);
                break;
            case GLFW_KEY_Q:
                camera->ProcessMovement(DOWN, deltaTime);
                break;
            default:
                break;
        }
    }
}

void UserInput::OnMouseChanged(double xpos, double ypos) {
    if(cameraMode) {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }
}
void UserInput::OnMouseScrollChanged(double xoffset, double yoffset) {
    if(cameraMode) {
        camera->ProcessMouseScroll(yoffset);
    }
}

void UserInput::OnMouseButton(int button, int action, int mods){
    if(!imGuiWrapper->WantCaptureMouse()){
        // click inside im gui does not trigger events for the main window
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
            glfwWrapper->ShowCursor(false);
            cameraMode = true;
        }

        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
            firstMouse = true;
            cameraMode = false;
            glfwWrapper->ShowCursor(true);
        }
    }
}
