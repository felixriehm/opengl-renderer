//
// Created by Felix on 24/09/2021.
//

#include <view/ImGuiWrapper.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cmath>
#include <view/GLFWWrapper.h>
#include <scene/Scene.h>
#include <texture/Texture.h>

using namespace View;

ImGuiWrapper::ImGuiWrapper(View::GLFWWrapper* glfwWrapper, Scene* scene) {
    this->glfwWrapper = glfwWrapper;
    this->scene = scene;
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

    if (showTransformSettings)
        ShowTransformSettings(&showTransformSettings);

    if (showTextureSettings)
        ShowTextureSettings(&showTextureSettings);

    ShowExampleAppSimpleOverlay(&showExampleAppSimpleOverlay);

    ShowMainMenuBar();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::ShowTransformSettings(bool* p_open){
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Transform (Local space)", p_open))
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

    static bool rotate = true;
    if(ImGui::Checkbox("Auto rotate object", &rotate)){
        scene->GetEntities().at(0)->SetAutoRotate(rotate);
    }

    ImGui::Spacing();

    ImGui::Text("Translate");

    ImGui::AlignTextToFramePadding();
    ImGui::Text("x:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float counter = 0;
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(-0.05f,0.0f,0.0f)); counter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(0.05f,0.0f,0.0f)); counter += 0.05f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", counter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("y:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float ycounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(0.0f,-0.05f,0.0f)); ycounter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(0.0f,0.05f,0.0f)); ycounter += 0.05f; };
    ImGui::SameLine();
    ImGui::Text("%.2f", ycounter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("z:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float zcounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(0.0f,0.0f,-0.05f)); zcounter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->MoveTo(glm::vec3(0.0f,0.0f,0.05f)); zcounter += 0.05f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", zcounter);

    ImGui::Spacing();

    ImGui::Text("Rotate");

    ImGui::AlignTextToFramePadding();
    ImGui::Text("x:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float rxcounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Rotate(-1.0f, glm::vec3(1,0,0)); rxcounter -= 1.0f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Rotate(1.0f, glm::vec3(1,0,0)); rxcounter += 1.0f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", rxcounter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("y:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float yrcounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Rotate(-1.0f, glm::vec3(0,1,0)); yrcounter -= 1.0f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Rotate(1.0f, glm::vec3(0,1,0)); yrcounter += 1.0f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", yrcounter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("z:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float zrcounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Rotate(-1.0f, glm::vec3(0,0,1)); zrcounter -= 1.0f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Rotate(1.0f, glm::vec3(0,0,1)); zrcounter += 1.0f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", zrcounter);

    ImGui::Spacing();

    ImGui::Text("Scale");

    ImGui::AlignTextToFramePadding();
    ImGui::Text("x:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float sxcounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Scale(glm::vec3(0.95f,1,1)); sxcounter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Scale(glm::vec3(1.05f,1,1)); sxcounter += 0.05f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", sxcounter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("y:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float yscounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Scale(glm::vec3(1, 0.95f,1)); yscounter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Scale(glm::vec3(1, 1.05f,1)); yscounter += 0.05f; }
    ImGui::SameLine();
    ImGui::Text("%.2f", yscounter);

    ImGui::AlignTextToFramePadding();
    ImGui::Text("z:");
    ImGui::SameLine();
    // Arrow buttons with Repeater
    static float zscounter = 0;
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { scene->GetEntities().at(0)->Scale(glm::vec3(1,1,0.95f)); zscounter -= 0.05f; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { scene->GetEntities().at(0)->Scale(glm::vec3(1,1,1.05f)); zscounter += 0.05f; }
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    ImGui::Text("%.2f", zscounter);

    ImGui::End();
}

void ImGuiWrapper::ShowTextureSettings(bool* p_open){
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
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

    ImGui::Text("Following texture settings can be applied:\n");               // Display some text (you can use a format strings too)

    ImGui::Text("Text coordinate scaling");
    static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
    static float xSlider = 1.0f;
    static float ySlider = 1.0f;
    if(ImGui::SliderFloat("x", &xSlider, 0.0f, 7.0f, "%.2f", flags)){
        scene->GetEntities().at(0)->GetRenderer()->ScaleTextCoord(0, xSlider);
    }
    if(ImGui::SliderFloat("y", &ySlider, 0.0f, 7.0f, "%.2f", flags)){
        scene->GetEntities().at(0)->GetRenderer()->ScaleTextCoord(1, xSlider);
    }

    ImGui::Spacing();

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
                scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(0)->SetTextureWrapping(item_current_idx);
                scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(1)->SetTextureWrapping(item_current_idx);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if(item_current_idx == 3){
        static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 1.0f);
        static bool alpha_preview = false;
        static bool alpha_half_preview = false;
        static bool drag_and_drop = true;
        static bool options_menu = true;
        static bool hdr = false;
        ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

        if(ImGui::ColorEdit3("Border color", (float*)&color, misc_flags)){
            float arrayColor[] = {color.x,color.y,color.z,color.w};
            scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(0)->SetTextureWrappingBorderColor(arrayColor);
            scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(1)->SetTextureWrappingBorderColor(arrayColor);
        }
        ImGui::SameLine(); HelpMarker(
                "Click on the color square to open a color picker.\n"
                "CTRL+click on individual component to input value.\n");
    }

    ImGui::Spacing();

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
                scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(0)->SetTextureFiltering(textureFilteringItem_current_idx);
                scene->GetEntities().at(0)->GetRenderer()->GetTextures().at(1)->SetTextureFiltering(textureFilteringItem_current_idx);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::End();
}

void ImGuiWrapper::HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
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
        ImGui::Text("Right click and hold inside the scene\n" "to control the camera with 'WASD/QE'.\n" "(right-click this window to change position)");
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

void ImGuiWrapper::ShowMainMenuBar() {
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
            ImGui::MenuItem("Transform", NULL, &showTransformSettings);
            ImGui::MenuItem("Texture", NULL, &showTextureSettings);
            if (ImGui::MenuItem("Lighting", NULL, false, false)) {}  // Disabled item
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
