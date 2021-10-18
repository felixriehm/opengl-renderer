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
#include <user_input/UserInput.h>
#include <utility/filesystem.h>
#include <scene/Scene.h>
#include <stb_image.h>
#include <glfw/glfw3.h>
#include <texture/Texture.h>

using namespace View;

void Gui::Run() {
    GLFWWrapper* glfwWrapper = new GLFWWrapper();
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Scene* scene = new Scene();
    OpenGLWrapper* openGl = new OpenGLWrapper(glfwWrapper);
    ImGuiWrapper* imGuiWrapper = new ImGuiWrapper(glfwWrapper, scene);
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

    Texture* tex1 = new Texture();
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(FileSystem::getPath("assets/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        tex1->Generate(width,height,data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    Texture* tex2 = new Texture();
    tex2->Internal_Format = GL_RGBA;
    tex2->Image_Format = GL_RGBA;
    data = stbi_load(FileSystem::getPath("assets/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        tex2->Generate(width,height,data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    std::vector<Texture*> textures = {tex1, tex2};


    Shader* cubeShader = new Shader(FileSystem::getPath("src/shader/main.vs").c_str(), FileSystem::getPath("src/shader/main.fs").c_str());
    Shader* lightShader = new Shader(FileSystem::getPath("src/shader/light.vs").c_str(), FileSystem::getPath("src/shader/light.fs").c_str());
    CubeRenderer* cubeRenderer = new CubeRenderer(cubeShader, textures, scene, glfwWrapper);
    LightRenderer* lightRenderer = new LightRenderer(lightShader, scene, glfwWrapper);
    Cube* cube = new Cube(glm::vec3(0.0f, 0.0f, 0.0f), cubeRenderer);
    Light* lightSource = new Light(glm::vec3(1.2f, 1.0f, 2.0f), lightRenderer);
    lightSource->Scale(glm::vec3(0.2f));
    scene->AddEntity(cube);
    scene->AddLight(lightSource);
    scene->SetCamera(camera);

    // render loop
    // -----------
    while (!glfwWrapper->ShouldWindowClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwWrapper->ProcessInput(deltaTime);

        openGl->ClearCanvas();

        scene->Draw(deltaTime);

        imGuiWrapper->RenderImGui();

        glfwWrapper->SwapBuffersAndPollIOEvents();
    }

    cubeRenderer->Cleanup();
    lightRenderer->Cleanup();
    imGuiWrapper->Cleanup();
    glfwWrapper->Cleanup();
}