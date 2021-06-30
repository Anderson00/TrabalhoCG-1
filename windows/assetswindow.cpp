#include "assetswindow.h"

AssetsWindow::AssetsWindow() : Window("Files", 0, 0, 0, 200)
{
    this->flags() = ImGuiWindowFlags_AlwaysVerticalScrollbar |
                    ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove;
}

void AssetsWindow::desenhar()
{
    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
    this->isCollpased() = ImGui::IsWindowCollapsed();
    float y = (this->isCollpased())? glutGet(GLUT_WINDOW_HEIGHT) - 19 : glutGet(GLUT_WINDOW_HEIGHT) - this->size().y;
    ImGui::SetWindowPos(ImVec2(0, y));
    float width = (this->inspectWindow()->isCollpased())? glutGet(GLUT_WINDOW_WIDTH) : glutGet(GLUT_WINDOW_WIDTH) - this->inspectWindow()->size().x;
    ImGui::SetWindowSize(ImVec2(width, this->size().y));

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Assets"))
        {
            ImVec2 button_sz(100, 40);
            ImGuiStyle& style = ImGui::GetStyle();
            std::vector<std::string> files = this->m_fileController->assets3DSFileNames();
            float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
            for (int n = 0; n < files.size(); n++)
            {
                ImGui::PushID(n);
                if(ImGui::Button(files[n].c_str(), button_sz)){
                    this->m_hierarchyWindow->addObjeto(this->m_fileController->get3DSfromAssetsFileName(files[n]));
                }
                float last_button_x2 = ImGui::GetItemRectMax().x;
                float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
                if (n + 1 < files.size() && next_button_x2 < window_visible_x2)
                    ImGui::SameLine();
                ImGui::PopID();
            }

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Primitives"))
        {

            ImVec2 button_sz(100, 40);
            ImGuiStyle& style = ImGui::GetStyle();
            std::vector<std::string> files({
                                               "Box", "Square", "Sphere", "Floor"
                                           });
            float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
            for (int n = 0; n < files.size(); n++)
            {
                ImGui::PushID(n);
                if(ImGui::Button(files[n].c_str(), button_sz)){

                }
                float last_button_x2 = ImGui::GetItemRectMax().x;
                float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
                if (n + 1 < files.size() && next_button_x2 < window_visible_x2)
                    ImGui::SameLine();
                ImGui::PopID();
            }


            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Scenes"))
        {

            ImVec2 button_sz(100, 40);
            ImGuiStyle& style = ImGui::GetStyle();
            std::vector<std::string> files = this->m_fileController->scenesFileNames();
            float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
            for (int n = 0; n < files.size(); n++)
            {
                ImGui::PushID(n);
                if(ImGui::Button(files[n].c_str(), button_sz)){
                    this->hierarchyWindow()->replaceObjetos(this->fileController()->openScene("Scenes/"+files[n]));
                }
                float last_button_x2 = ImGui::GetItemRectMax().x;
                float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
                if (n + 1 < files.size() && next_button_x2 < window_visible_x2)
                    ImGui::SameLine();
                ImGui::PopID();
            }


            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

HierarchyWindow *AssetsWindow::hierarchyWindow()
{
    return this->m_hierarchyWindow;
}

HierarchyWindow *AssetsWindow::hierarchyWindow(HierarchyWindow *window)
{
    this->m_hierarchyWindow = window;
    return this->m_hierarchyWindow;
}

InspectWindow *AssetsWindow::inspectWindow()
{
    return this->m_inspectWindow;
}

InspectWindow *AssetsWindow::inspectWindow(InspectWindow *window)
{
    this->m_inspectWindow = window;
    return this->m_inspectWindow;
}

FileController *AssetsWindow::fileController()
{
    return this->m_fileController;
}

FileController *AssetsWindow::fileController(FileController *controller)
{
    this->m_fileController = controller;
    return this->m_fileController;
}
