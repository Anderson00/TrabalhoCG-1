#include "keyinputwindow.h"

KeyInputWindow::KeyInputWindow() : Window("Input")
{
    this->flags() = ImGuiWindowFlags_AlwaysAutoResize |
                    ImGuiWindowFlags_NoMove |
                    //ImGuiWindowFlags_NoBackground |
                    ImGuiWindowFlags_NoTitleBar;
    ImVec2& pos = this->position();
    pos.x = 0;
    pos.y = 19;

}

void KeyInputWindow::desenhar()
{
    ImGui::SetNextWindowBgAlpha(0.1);
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
    ImGui::SetWindowPos(this->position());

    ImGuiIO& io = ImGui::GetIO();

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("width: %d, height: %d", glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    ImGui::Separator();
    ImGui::Text("Pressed: %d %.2f", io.MouseDown[0], (io.MouseDownDuration[0] >= 0)? io.MouseDownDuration[0] : 0);
    ImGui::Text("X:%.2f, Y:%.2f", io.MousePos.x, io.MousePos.y);
    ImGui::Text("Last key: %c", this->m_key);

    ImGui::End();
}

unsigned int &KeyInputWindow::key()
{
    return this->m_key;
}
