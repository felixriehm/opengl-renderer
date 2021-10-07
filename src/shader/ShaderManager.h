//
// Created by Felix on 06/10/2021.
//

#ifndef OPENGL_RENDERER_SHADERMANAGER_H
#define OPENGL_RENDERER_SHADERMANAGER_H
#include <shader/shader_m.h>
#include <list>

class ShaderManager {
    public:
        static Shader GetShader(int shader);
        static int CreateShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    private:
        ShaderManager() {};
        static std::list<Shader> ShaderList;
};


#endif //OPENGL_RENDERER_SHADERMANAGER_H
