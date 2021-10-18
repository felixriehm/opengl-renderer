//
// Created by Felix on 17/10/2021.
//

#include "Scene.h"

void Scene::Draw(float deltaTime) {
    for (int i = 0; i < Entities.size(); ++i) {
        Entities.at(i)->Draw(deltaTime);
    }
    for (int i = 0; i < Lights.size(); ++i) {
        Lights.at(i)->Draw();
    }
}
void Scene::SetCamera(Camera* camera){
    this->camera = camera;
}
Camera* Scene::GetCamera(){
    return camera;
}
void Scene::AddEntity(Cube* cube){
    this->Entities.push_back(cube);
}
std::vector<Cube*> Scene::GetEntities(){
    return Entities;
}
void Scene::AddLight(Light* light){
    Lights.push_back(light);
}
std::vector<Light*> Scene::GetLights(){
    return Lights;
}