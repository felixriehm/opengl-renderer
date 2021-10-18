//
// Created by Felix on 14/10/2021.
//

#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Light::Light(glm::vec3 position, LightRenderer* lightRenderer) {
    this->position = position;
    this->MoveTo(position);
    this->lightRenderer = lightRenderer;
}

void Light::Draw() {
    lightRenderer->Render(model);
}

glm::vec3 Light::GetPosition(){
    return position;
}

void Light::MoveTo(glm::vec3 position){
    this->position = position;
    model = glm::translate(model, glm::vec3(position));
}

void Light::Scale(glm::vec3 scale){
    this->scale = scale;
    model = glm::scale(model, glm::vec3(scale)); // last scale
}

void Light::Rotate(float rotate, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(rotate), axis); // then rotate
}