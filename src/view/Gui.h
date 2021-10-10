//
// Created by Felix on 24/09/2021.
//

#ifndef OPENGL_RENDERER_GUI_H
#define OPENGL_RENDERER_GUI_H

#include <string>

namespace View {
    class Gui {
        public:
            void Run();
        private:
            const std::string VertexShaderPath = "src/shader/main.vs";
            const std::string FragmentShaderPath = "src/shader/main.fs";
            float deltaTime = 0.0f;
            float lastFrame = 0.0f;
    };
}

#endif //OPENGL_RENDERER_GUI_H
