#include "hierarchywindow.h"

HierarchyWindow::HierarchyWindow() : Window("Hierarchy", 0, 0, 150, 200)
{
    this->flags() = ImGuiWindowFlags_AlwaysVerticalScrollbar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove;
}

void HierarchyWindow::desenhar()
{
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
    ImGui::SetWindowPos(ImVec2(glutGet(GLUT_WINDOW_WIDTH) -  this->size().x, 19));
    ImGui::SetWindowSize(this->size());

    for(int i = 0; i < 50; i++){
        ImGui::Text("Count: %d", i);
    }

    ImGui::End();
}
