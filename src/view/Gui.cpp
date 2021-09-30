//
// Created by Felix on 24/09/2021.
//

#include "Gui.h"
#include "GLFWWrapper.h"
#include <view/ImGuiWrapper.h>
#include "OpenGLWrapper.h"
#include <excpetions/GLFWException.h>
#include <excpetions/GLEWException.h>
#include <iostream>

using namespace View;

void Gui::Run() {
    GLFWWrapper* glfwWrapper = new GLFWWrapper();
    OpenGLWrapper* openGl = new OpenGLWrapper();
    ImGuiWrapper* imGuiWrapper = new ImGuiWrapper(glfwWrapper, openGl);

    try {
        glfwWrapper->Init();
        glfwWrapper->CreateWindow();
        openGl->Init();
        imGuiWrapper->Init();
    } catch (const Exception::GLFWException& e) {
        std::cout << "GLFW exception: " << e.what() << std::endl;
        throw;
    } catch (const Exception::GLEWException& e) {
        glfwWrapper->TerminateWindow();
        std::cerr << "glewInit failed: " << e.what() << std::endl;
        throw;
    }

    openGl->BuildAndCompileShaderProgram(VertexShaderPath,FragmentShaderPath);

    // load vertices
    {
        float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        openGl->SetupVerticeData(vertices);
    }

    openGl->LoadAndCreateTextures((std::string []){ "assets/textures/container.jpg", "assets/textures/awesomeface.png"});

    imGuiWrapper->ConfigureImgui();

    // render loop
    // -----------
    while (!glfwWrapper->ShouldWindowClose())
    {
        glfwWrapper->ProcessInput();

        imGuiWrapper->RenderImGui();

        openGl->ClearCanvas();

        imGuiWrapper->RenderDrawData();

        openGl->CreateTransformations();

        openGl->Draw();

        glfwWrapper->SwapBuffersAndPollIOEvents();
    }

    openGl->Cleanup();
    imGuiWrapper->Cleanup();
    glfwWrapper->Cleanup();
}