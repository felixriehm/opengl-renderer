//
// Created by Felix on 09/10/2021.
//

#ifndef OPENGL_RENDERER_USERINPUT_H
#define OPENGL_RENDERER_USERINPUT_H

namespace View
{
    class ImGuiWrapper;
}
namespace View
{
    class GLFWWrapper;
}
class Camera;

class UserInput {
    public:
        UserInput(View::GLFWWrapper* glfwWrapper, Camera* camera, View::ImGuiWrapper* imGuiWrapper);
        void Init();
    private:
        UserInput();
        View::GLFWWrapper* glfwWrapper;
        View::ImGuiWrapper* imGuiWrapper;
        Camera* camera;
        void OnKeyPressed(int key, float deltaTime);
        void OnMouseButton(int button, int action, int mods);
        void OnMouseChanged(double xpos, double ypos);
        void OnMouseScrollChanged(double xoffset, double yoffset);
        float lastX;
        float lastY;
        bool firstMouse = true;
        bool cameraMode = false;
};


#endif //OPENGL_RENDERER_USERINPUT_H
