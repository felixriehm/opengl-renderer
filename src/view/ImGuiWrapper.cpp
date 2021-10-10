//
// Created by Felix on 24/09/2021.
//

#include <view/ImGuiWrapper.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cmath>

using namespace View;

ImGuiWrapper::ImGuiWrapper(GLFWWrapper* glfwWrapper, OpenGLWrapper* openGlWrapper) {
    this->glfwWrapper = glfwWrapper;
    this->openGlWrapper = openGlWrapper;
}

void ImGuiWrapper::Init(){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwWrapper->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO(); (void)io;
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

    // for documentation and reference
    //ImGui::ShowDemoWindow();

    static bool showTextureSettings = false;
    static bool showExampleAppSimpleOverlay = true;

    if (showTextureSettings)
        ShowTextureSettings(&showTextureSettings);

    ShowExampleAppSimpleOverlay(&showExampleAppSimpleOverlay);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", NULL, false, false)) {}
            if (ImGui::MenuItem("Open", NULL, false, false)) {}
            if (ImGui::MenuItem("Save", NULL, false, false)) {}
            ImGui::Separator();
            if (ImGui::BeginMenu("Options", false))
            {
                static bool enabled = true;
                ImGui::MenuItem("Enabled", "", &enabled);
                ImGui::BeginChild("child", ImVec2(0, 60), true);
                for (int i = 0; i < 10; i++)
                    ImGui::Text("Scrolling Text %d", i);
                ImGui::EndChild();
                static float f = 0.5f;
                static int n = 0;
                ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                ImGui::InputFloat("Input", &f, 0.1f);
                ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                ImGui::EndMenu();
            }

            // Here we demonstrate appending again to the "Options" menu (which we already created above)
            // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
            // In a real code-base using it would make senses to use this feature from very different code locations.
            if (ImGui::BeginMenu("Options")) // <-- Append!
            {
                static bool b = true;
                ImGui::Checkbox("SomeOption", &b);
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                glfwWrapper->WindowShouldClose();
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Transform", NULL, false, false)) {}
            ImGui::MenuItem("Texture", NULL, &showTextureSettings);
            if (ImGui::MenuItem("Lighting", NULL, false, false)) {}  // Disabled item
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ImGuiWrapper::ShowTextureSettings(bool* p_open){
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Texture", p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Console"))
            *p_open = false;
        ImGui::EndPopup();
    }

    ImGui::Text("Following texture settings can be applied:");               // Display some text (you can use a format strings too)

    const char* items[] = { "Repeat", "Mirrored repeat", "Clamp to edge", "Clamp to border" };
    static int item_current_idx = 0; // Here we store our selection data as an index.
    const char* combo_preview_value = items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo("Texture wrapping", combo_preview_value))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected)){
                item_current_idx = n;
                openGlWrapper->SetTextureWrapping(item_current_idx);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    const char* textureFilteringItems[] = { "Linear", "Nearest" };
    static int textureFilteringItem_current_idx = 0; // Here we store our selection data as an index.
    const char* textureFilteringCombo_preview_value = textureFilteringItems[textureFilteringItem_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo("Texture filtering", textureFilteringCombo_preview_value))
    {
        for (int n = 0; n < IM_ARRAYSIZE(textureFilteringItems); n++)
        {
            const bool is_selected = (textureFilteringItem_current_idx == n);
            if (ImGui::Selectable(textureFilteringItems[n], is_selected)){
                textureFilteringItem_current_idx = n;
                openGlWrapper->SetTextureFiltering(textureFilteringItem_current_idx);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::End();
}

void ImGuiWrapper::ShowExampleAppSimpleOverlay(bool* p_open)
{
    static int corner = 1;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (corner != -1)
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Info:", p_open, window_flags))
    {
        ImGui::Text("Click inside the scene to control the camera with 'WASD'.\n" "Press 'ESC' to leave the camera mode.\n" "(right-click this window to change position)");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Separator();
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse Position: <invalid>");
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Custom",       NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left",     NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right",    NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left",  NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            if (p_open && ImGui::MenuItem("Close")) *p_open = false;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

bool ImGuiWrapper::WantCaptureMouse() {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    return io.WantCaptureMouse;
}

bool ImGuiWrapper::WantCaptureKeyboard() {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    return io.WantCaptureKeyboard;
}

void ImGuiWrapper::Cleanup() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
