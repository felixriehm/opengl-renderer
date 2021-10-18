//
// Created by Felix on 14/10/2021.
//

#include "CubeRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scene/Scene.h>
#include <texture/Texture.h>

CubeRenderer::CubeRenderer(Shader* shader, std::vector<Texture*> textures, Scene* scene, View::GLFWWrapper* glfwWrapper){
    this->shader = shader;
    this->scene = scene;
    this->glfwWrapper = glfwWrapper;
    this->textures = textures;
    InitRenderData();
}

void CubeRenderer::InitRenderData(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    this->shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
    shader->setFloat("xTextCoordScale", 1.0);
    shader->setFloat("yTextCoordScale", 1.0);
}

void CubeRenderer::Render(glm::mat4 model){
    this->shader->use();

    view  = scene->GetCamera()->GetViewMatrix();
    projection = glm::perspective(glm::radians(scene->GetCamera()->Zoom), (float)this->glfwWrapper->GetScreenDimensions().x / (float)this->glfwWrapper->GetScreenDimensions().y, 0.1f, 100.0f);
    // create transformations

    shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    // commented in favor of texture color
    //shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
    shader->setVec3("lightPos", scene->GetLights().at(0)->GetPosition());
    shader->setVec3("viewPos", scene->GetCamera()->Position);

    glActiveTexture(GL_TEXTURE0);
    textures.at(0)->Bind();
    glActiveTexture(GL_TEXTURE1);
    textures.at(1)->Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void CubeRenderer::ScaleTextCoord(int axis, float scale){
    this->shader->use();

    if(axis == 0) {
        // x axis
        this->shader->setFloat("xTextCoordScale", scale);
    } else {
        // y axis
        this->shader->setFloat("yTextCoordScale", scale);
    }
}

std::vector<Texture*> CubeRenderer::GetTextures() {
    return textures;
}

void CubeRenderer::Cleanup() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}