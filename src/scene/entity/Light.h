//
// Created by Felix on 14/10/2021.
//

#ifndef OPENGL_RENDERER_LIGHT_H
#define OPENGL_RENDERER_LIGHT_H


#include <renderer/LightRenderer.h>

class Light {
public:
    Light(glm::vec3 position, LightRenderer* lightRenderer);
    void Draw();
    void MoveTo(glm::vec3 position);
    glm::vec3 GetPosition();
    void Scale(glm::vec3 scale);
    void Rotate(float rotate, glm::vec3 axis);
private:
    glm::vec3 position;
    glm::vec3 scale;
    LightRenderer* lightRenderer;
    glm::mat4 model = glm::mat4(1.0f);
};


#endif //OPENGL_RENDERER_LIGHT_H
