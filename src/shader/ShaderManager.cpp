//
// Created by Felix on 06/10/2021.
//

#include "ShaderManager.h"
#include <iterator>

std::list<Shader> ShaderManager::ShaderList;

Shader ShaderManager::GetShader(int shader) {
    auto shaderIterator = ShaderList.begin();
    std::advance(shaderIterator, shader);
    return *shaderIterator;
}

int ShaderManager::CreateShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath){
    ShaderList.push_back(Shader(vertexPath,fragmentPath,geometryPath));
    return ShaderList.size();
}
