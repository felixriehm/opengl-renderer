//
// Created by Felix on 13/10/2021.
//

#include "Cube.h"
#include <glew/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(glm::vec3 position, CubeRenderer* cubeRenderer) {
    MoveTo(position);
    this->cubeRenderer = cubeRenderer;
}

void Cube::Draw(float deltaTime) {
    if (autoRotate){
        Rotate(40.0f*deltaTime, glm::vec3(0.5f, 1.0f, 0.0f));
    }
    cubeRenderer->Render(model);
}

void Cube::MoveTo(glm::vec3 position){
    // moves cube from current position by position vector
    model = glm::translate(model, glm::vec3(position));
}

void Cube::Scale(glm::vec3 scale){
    model = glm::scale(model, glm::vec3(scale)); // last scale
}

void Cube::Rotate(float rotate, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(rotate), axis); // then rotate
}

void Cube::SetAutoRotate(bool rotate){
    autoRotate = rotate;
}

CubeRenderer* Cube::GetRenderer(){
    return cubeRenderer;
}
