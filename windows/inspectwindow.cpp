#include "inspectwindow.h"

InspectWindow::InspectWindow() : Window("Inspect", 0, 0, 250, 300)
{
    this->flags() = ImGuiWindowFlags_AlwaysVerticalScrollbar |
            ImGuiWindowFlags_AlwaysHorizontalScrollbar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove;
}

void InspectWindow::desenhar()
{
    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
    float y = (this->m_hierarchyWindow->isCollpased())? 19*2 : this->m_hierarchyWindow->size().y + 19;
    ImGui::SetWindowPos(ImVec2(glutGet(GLUT_WINDOW_WIDTH) -  this->size().x, y));
    ImGui::SetWindowSize(this->size());

    if(this->m_hierarchyWindow != nullptr && this->m_hierarchyWindow->objetos().size() > 0){
        if(this->m_hierarchyWindow->itemIndiceSelected() >= 0){
            Objeto *objeto = this->m_hierarchyWindow->objetos()[this->m_hierarchyWindow->itemIndiceSelected()];
            if(ImGui::Button("Deletar")){
                this->m_hierarchyWindow->removeObjeto(this->m_hierarchyWindow->itemIndiceSelected());
                this->m_hierarchyWindow->itemIndiceSelected() = -1;
            }
            static char name[255];
            memset(name, 0, 255);
            memcpy(name, objeto->nome().c_str(), objeto->nome().size());

            ImGui::Text("Name:");
            ImGui::InputText("", name, 255);
            objeto->nome() = name;
            ImGui::Separator();
            ImGui::Text("    X      Y       Z");
            float *translateOfObject[3] = {&objeto->t.x, &objeto->t.y, &objeto->t.z};
            float *rotationOfObject[3] = {&objeto->a.x, &objeto->a.y, &objeto->a.z};
            float *scaleOfObject[3] = {&objeto->s.x, &objeto->s.y, &objeto->s.z};

            if(*rotationOfObject[0] == 360 || *rotationOfObject[0] == -360)
                *rotationOfObject[0] = 0;
            if(*rotationOfObject[1] == 360 || *rotationOfObject[1] == -360)
                *rotationOfObject[0] = 0;
            if(*rotationOfObject[2] == 360 || *rotationOfObject[2] == -360)
                *rotationOfObject[0] = 0;
            ImGui::DragFloat3("Translate", translateOfObject[0], 0.05f, -50.0f, 50.0f);
            ImGui::DragFloat3("Rotation", rotationOfObject[0], 0.05f, -360.0f, 360.0f);
            ImGui::DragFloat3("Scale", scaleOfObject[0], 0.05f, -50.0f, 50.0f);
            ImGui::Separator();
        }
    }

    ImGui::End();
}

HierarchyWindow *InspectWindow::hierarchyWindow()
{
    return this->m_hierarchyWindow;
}

HierarchyWindow *InspectWindow::hierarchyWindow(HierarchyWindow *window)
{
    this->m_hierarchyWindow = window;
    return this->m_hierarchyWindow;
}