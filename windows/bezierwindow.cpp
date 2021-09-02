#include "bezierwindow.h"

BezierWindow::BezierWindow() : Window("Bezier", 0, 0, 200, 200)
{

}

void BezierWindow::desenhar()
{
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
        //ImGui::SetWindowPos(ImVec2(glutGet(GLUT_WINDOW_WIDTH) -  this->size().x, 19));
        ImGui::SetWindowSize(this->size());
        this->isCollpased() = ImGui::IsWindowCollapsed();

        ImGui::Text("Pontos de Controle");
        float *translateOfObject[2] = {&p0[0], &p0[1]};

        ImGui::DragFloat2("p(0)", translateOfObject[0], 0.05f, -50.0f, 50.0f);
        ImGui::Separator();
        float *translateOfObject2[2] = {&p1[0], &p1[1]};

        ImGui::DragFloat2("p(1)", translateOfObject2[0], 0.05f, -50.0f, 50.0f);
        ImGui::Separator();
        float *translateOfObject3[2] = {&p2[0], &p2[1]};

        ImGui::DragFloat2("p(2)", translateOfObject3[0], 0.05f, -50.0f, 50.0f);
        ImGui::Separator();
        float *translateOfObject4[2] = {&p3[0], &p3[1]};

        ImGui::DragFloat2("p(3)", translateOfObject4[0], 0.05f, -50.0f, 50.0f);
        ImGui::Separator();


    ImGui::End();
}
