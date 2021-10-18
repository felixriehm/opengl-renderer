//
// Created by Felix on 13/10/2021.
//

#ifndef OPENGL_RENDERER_CUBE_H
#define OPENGL_RENDERER_CUBE_H

#include <vector>
#include <glm/glm.hpp>
#include <shader/shader_m.h>
#include <renderer/CubeRenderer.h>

class Cube {
public:
    Cube(glm::vec3 position, CubeRenderer* cubeRenderer);
    void Draw(float deltaTime);
    void MoveTo(glm::vec3 position);
    void Scale(glm::vec3 scale);
    void Rotate(float rotate, glm::vec3 axis);
    void SetAutoRotate(bool rotate);
    CubeRenderer* GetRenderer();
private:
    std::vector<Texture*> textures;
    CubeRenderer* cubeRenderer;
    glm::mat4 model = glm::mat4(1.0f);
    bool autoRotate = true;
};


#endif //OPENGL_RENDERER_CUBE_H
