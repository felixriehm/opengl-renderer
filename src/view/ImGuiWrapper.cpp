//
// Created by Felix on 24/09/2021.
//

#include <view/ImGuiWrapper.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace View;

ImGuiWrapper::ImGuiWrapper(GLFWWrapper* glfwWrapper, OpenGLWrapper* openGlWrapper) {
    this->glfwWrapper = glfwWrapper;
    this->openGlWrapper = openGlWrapper;
}

void ImGuiWrapper::Init(){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwWrapper->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    io.Fonts->AddFontFromFileTTF("../assets/fonts/Roboto-Medium.ttf", round(this->glfwWrapper->GetScreenDimensions().x/1200 * 16.0f));

    // after changing font
    ImGuiStyle * style = &ImGui::GetStyle();
    style->ScaleAllSizes(2);
}

void ImGuiWrapper::RenderImGui() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;
        bool show_demo_window = true;
        bool show_another_window = false;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImVec4 clear_color = ImVec4(openGlWrapper->GetClearColor().x, openGlWrapper->GetClearColor().y, openGlWrapper->GetClearColor().z, openGlWrapper->GetClearColor().w);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    ImGui::Render();
}

void ImGuiWrapper::RenderDrawData() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::Cleanup() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
