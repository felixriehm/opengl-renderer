//
// Created by Felix on 24/09/2021.
//

#include <glew/glew.h>
#include <shader/ShaderManager.h>
#include <view/OpenGLWrapper.h>
#include <excpetions/GLEWException.h>
#include <utility/filesystem.h>
#include <stb_image.h>
#include <iostream>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace View;

OpenGLWrapper::OpenGLWrapper(GLFWWrapper* glfwWrapper, Camera* camera){
    this->glfwWrapper = glfwWrapper;
    this->camera = camera;
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

void OpenGLWrapper::BuildAndCompileShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
    // build and compile our shader zprogram
    // ------------------------------------
    ShaderManager::CreateShader(FileSystem::getPath(vertexShaderPath).c_str(), FileSystem::getPath(fragmentShaderPath).c_str());
}

void OpenGLWrapper::SetupVerticeData(std::vector<float> vertices) {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void OpenGLWrapper::LoadAndCreateTextures(std::string texturePaths[]){
    // load and create a texture
    // -------------------------

    // texture 1
    // ---------
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // set the texture wrapping parameters
    SetTextureWrapping(0, textures[0]);
    // set texture filtering parameters
    SetTextureFiltering(0, textures[0]);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(FileSystem::getPath(texturePaths[0]).c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &textures[1]);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    // set the texture wrapping parameters
    SetTextureWrapping(0, textures[1]);
    // set texture filtering parameters
    SetTextureFiltering(0, textures[1]);
    // load image, create texture and generate mipmaps
    data = stbi_load(FileSystem::getPath(texturePaths[1]).c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGLWrapper the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    Shader s = ShaderManager::GetShader(0);
    s.use();
    s.setInt("texture1", 0);
    s.setInt("texture2", 1);
    s.setFloat("xTextCoordScale", 1.0);
    s.setFloat("yTextCoordScale", 1.0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
}

void OpenGLWrapper::ClearCanvas() {
    glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
}

glm::vec4 OpenGLWrapper::GetClearColor() {
    return this->ClearColor;
}

void OpenGLWrapper::CreateTransformations(float deltaTime){
    // activate shader
    Shader shader = ShaderManager::GetShader(0);
    shader.use();

    // create transformations
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    if(rotateObject){
        model = glm::rotate(model, glm::radians(40.0f*deltaTime), glm::vec3(0.5f, 1.0f, 0.0f));
    }
    view  = camera->GetViewMatrix();
    projection = glm::perspective(glm::radians(camera->Zoom), (float)this->glfwWrapper->GetScreenDimensions().x / (float)this->glfwWrapper->GetScreenDimensions().y, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
}

void OpenGLWrapper::AutoRotateObject(bool rotate) {
    rotateObject = rotate;
}

void OpenGLWrapper::RotateObject(int axis, float angle) {
    switch (axis) {
        case 0:
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 1:
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case 2:
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        default:
            break;
    }
}

void OpenGLWrapper::TranslateObject(int axis, float translate) {
    switch (axis) {
        case 0:
            model = glm::translate(model, glm::vec3(translate,0.0f,0.0f));
            break;
        case 1:
            model = glm::translate(model, glm::vec3(0.0f,translate,0.0f));
            break;
        case 2:
            model = glm::translate(model, glm::vec3(0.0f,0.0f,translate));
            break;
        default:
            break;
    }
}

void OpenGLWrapper::ScaleObject(int axis, float scale) {
    switch (axis) {
        case 0:
            model = glm::scale(model, glm::vec3(scale,1.0f,1.0f));
            break;
        case 1:
            model = glm::scale(model, glm::vec3(1.0f,scale,1.0f));
            break;
        case 2:
            model = glm::scale(model, glm::vec3(1.0f,1.0f,scale));
            break;
        default:
            break;
    }
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void OpenGLWrapper::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void OpenGLWrapper::Draw() {
    // render box
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void OpenGLWrapper::Cleanup() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void OpenGLWrapper::SetTextureWrapping(int i, int texture) {

    auto setTextureWrapping = [](int i)
    {
        switch (i) {
            case 0:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                break;
            case 1:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
                break;
            case 2:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                break;
            case 3:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                break;
            default:
                break;
        }
    };

    if(texture == -1){
        for (int j = 0; j < 2; ++j) {
            glBindTexture(GL_TEXTURE_2D, textures[j]);
            setTextureWrapping(i);
        }
    }else {
        glBindTexture(GL_TEXTURE_2D, texture);
        setTextureWrapping(i);
    }


}

void OpenGLWrapper::ScaleTextCoord(int axis, float scale){
    Shader s = ShaderManager::GetShader(0);
    s.use();

    if(axis == 0) {
        // x axis
        s.setFloat("xTextCoordScale", scale);
    } else {
        // y axis
        s.setFloat("yTextCoordScale", scale);
    }
}

void OpenGLWrapper::SetTextureWrappingBorderColor(float borderColor[]){
    for (int j = 0; j < 2; ++j) {
        glBindTexture(GL_TEXTURE_2D, textures[j]);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
}

void OpenGLWrapper::SetTextureFiltering(int i, int texture) {

    auto setTextureFiltering = [](int i)
    {
        switch (i) {
            case 0:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                break;
            case 1:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                break;
            default:
                break;
        }
    };

    if(texture == -1){
        for (int j = 0; j < 2; ++j) {
            glBindTexture(GL_TEXTURE_2D, textures[j]);
            setTextureFiltering(i);
        }
    }else {
        glBindTexture(GL_TEXTURE_2D, texture);
        setTextureFiltering(i);
    }
}
