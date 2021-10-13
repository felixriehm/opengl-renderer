//
// Created by Felix on 24/09/2021.
//
#include "Gui.h"
#include <view/GLFWWrapper.h>
#include <view/ImGuiWrapper.h>
#include <view/OpenGLWrapper.h>

#include <excpetions/GLFWException.h>
#include <excpetions/GLEWException.h>
#include <iostream>
#include <vector>
#include <camera/Camera.h>
#include <user_input/UserInput.h>

using namespace View;

void Gui::Run() {
    GLFWWrapper* glfwWrapper = new GLFWWrapper();
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    OpenGLWrapper* openGl = new OpenGLWrapper(glfwWrapper, camera);
    ImGuiWrapper* imGuiWrapper = new ImGuiWrapper(glfwWrapper, openGl);
    UserInput* userInput = new UserInput(glfwWrapper, camera, imGuiWrapper);

    try {
        glfwWrapper->Init();
        glfwWrapper->CreateWindow();
        openGl->Init();
        imGuiWrapper->Init();
        userInput->Init();
    } catch (const Exception::GLFWException& e) {
        std::cout << "GLFW exception: " << e.what() << std::endl;
        throw;
    } catch (const Exception::GLEWException& e) {
        glfwWrapper->TerminateWindow();
        std::cerr << "glewInit failed: " << e.what() << std::endl;
        throw;
    }

    std::vector<std::string> vsPaths = {"src/shader/main.vs", "src/shader/light.vs"};
    std::vector<std::string> fsPaths = {"src/shader/main.fs", "src/shader/light.fs"};
    openGl->BuildAndCompileShaderProgram(vsPaths,fsPaths);

    // load vertices
    {
        const std::vector<float> vertices {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
        };
        openGl->SetupVerticeData(vertices);
    }

    std::string texturePaths[2] = {"assets/textures/container.jpg", "assets/textures/awesomeface.png"};
    openGl->LoadAndCreateTextures(texturePaths);

    //openGl->CreateTransformationsInit();

    // render loop
    // -----------
    while (!glfwWrapper->ShouldWindowClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwWrapper->ProcessInput(deltaTime);

        openGl->ClearCanvas();

        openGl->CreateTransformations(deltaTime);

        openGl->Draw();

        imGuiWrapper->RenderImGui();

        glfwWrapper->SwapBuffersAndPollIOEvents();
    }

    openGl->Cleanup();
    imGuiWrapper->Cleanup();
    glfwWrapper->Cleanup();
}