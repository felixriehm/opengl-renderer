//
// Created by Felix on 17/10/2021.
//

#ifndef OPENGL_RENDERER_SCENE_H
#define OPENGL_RENDERER_SCENE_H


#include <scene/camera/Camera.h>
#include <scene/entity/Cube.h>
#include <scene/entity/Light.h>

class Scene {
    public:
        void SetCamera(Camera* camera);
        Camera* GetCamera();
        void AddEntity(Cube* cube);
        std::vector<Cube*> GetEntities();
        void AddLight(Light* light);
        std::vector<Light*> GetLights();
        void Draw(float deltaTime);
    private:
        Camera* camera;
        std::vector<Cube*> Entities;
        std::vector<Light*> Lights;
};


#endif //OPENGL_RENDERER_SCENE_H
