//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_GLFWWRAPPER_H
#define OPENGL_RENDERER_GLFWWRAPPER_H
#include <glm/glm.hpp>
#include <boost/signals2/signal.hpp>

struct GLFWwindow;

namespace View {
    class GLFWWrapper {
        public:
            void Init();
            void CreateWindow();
            GLFWwindow* GetWindow();
            void TerminateWindow();
            void ProcessInput(float deltaTime);
            bool ShouldWindowClose();
            glm::vec2 GetScreenDimensions();
            void Cleanup();
            void ShowCursor(bool show);
            void WindowShouldClose();
            void SwapBuffersAndPollIOEvents();
            boost::signals2::signal<void (int, float)>* OnKeyPressed();
            boost::signals2::signal<void (int, int, int)>* OnMouseButton();
            boost::signals2::signal<void (double, double)>* OnMouseChanged();
            boost::signals2::signal<void (double, double)>* OnMouseScrollChanged();
        private:
            // settings
            unsigned int ScreenWidth = 2400;
            unsigned int ScreenHeight = 1400;
            GLFWwindow* window;
            // this is needed to access 'this' object inside the static method MouseCallback and ScrollCallback
            // GLFW needs a static method to bind callbacks
            static GLFWWrapper* thisObject;
            static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
            static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            boost::signals2::signal<void (int, float)>* onKeyPressed;
            boost::signals2::signal<void (int, int, int)>* onMouseButton;
            boost::signals2::signal<void (double, double)>* onMouseChanged;
            boost::signals2::signal<void (double, double)>* onMouseScrollChanged;
    };
}

#endif //OPENGL_RENDERER_GLFWWRAPPER_H
