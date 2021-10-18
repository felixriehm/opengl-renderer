//
// Created by Felix on 14/10/2021.
//

#include "LightRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scene/Scene.h>

LightRenderer::LightRenderer(Shader* shader, Scene* scene, View::GLFWWrapper* glfwWrapper){
    this->shader = shader;
    this->scene = scene;
    this->glfwWrapper = glfwWrapper;
    this->InitRenderData();
}

void LightRenderer::InitRenderData(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void LightRenderer::Render(glm::mat4 model){
    this->shader->use();

    view  = this->scene->GetCamera()->GetViewMatrix();
    projection = glm::perspective(glm::radians(this->scene->GetCamera()->Zoom), (float)this->glfwWrapper->GetScreenDimensions().x / (float)this->glfwWrapper->GetScreenDimensions().y, 0.1f, 100.0f);

    this->shader->setMat4("model", model);
    this->shader->setMat4("projection", projection);
    this->shader->setMat4("view", view);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void LightRenderer::Cleanup() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}