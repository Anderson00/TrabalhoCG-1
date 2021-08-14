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

    this->m_mouseX = io.MousePos.x;
    this->m_mouseY = io.MousePos.y;

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("width: %d, height: %d", glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    ImGui::Separator();
    ImGui::Text("Pressed: %d %.2f", io.MouseDown[0], (io.MouseDownDuration[0] >= 0)? io.MouseDownDuration[0] : 0);
    ImGui::Text("X:%.2f, Y:%.2f", io.MousePos.x, io.MousePos.y);
    ImGui::Text("Last key: %c", this->m_key);
    ImGui::Separator();

    ImGui::Checkbox("Insertion", &this->m_inInsertionMode);
    ImGui::SameLine();
    ImGui::Checkbox("Transform Mode", &this->m_inTransformationMode);
    ImGui::Separator();
    ImGui::Checkbox("Translate", &this->m_inTranslateMode);
    ImGui::SameLine();
    ImGui::Checkbox("Rotate", &this->m_inRotationMode);
    ImGui::SameLine();
    ImGui::Checkbox("Scale", &this->m_inScaleMode);
    ImGui::Separator();
    ImGui::Checkbox("Keyboard Actions Locked", &this->m_iskeyboardActionsLocked);
    ImGui::Separator();
    ImGui::Text("Projections");

    // Simple selection popup
    // (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
    if (ImGui::Button("selecionar.."))
        ImGui::OpenPopup("my_select_popup");
    ImGui::SameLine();
    ImGui::TextUnformatted(this->m_projectionMode == -1 ? "<None>" : this->m_projectioNames[this->m_projectionMode]);
    if (ImGui::BeginPopup("my_select_popup"))
    {
        ImGui::Text("Projeções");
        ImGui::Separator();
        for (int i = 0; i < IM_ARRAYSIZE(this->m_projectioNames); i++)
            if (ImGui::Selectable(this->m_projectioNames[i]))
                glutGUI::perspective = this->m_projectionMode = i;
        ImGui::EndPopup();
    }

    ImGui::End();
}

unsigned int &KeyInputWindow::key()
{
    return this->m_key;
}

bool &KeyInputWindow::inInsertionMode()
{
    return this->m_inInsertionMode;
}

bool &KeyInputWindow::inTransformationMode()
{
    return this->m_inTransformationMode;
}

bool &KeyInputWindow::inTranslateMode()
{
    return this->m_inTranslateMode;
}

bool &KeyInputWindow::inRotationMode()
{
    return this->m_inRotationMode;
}

bool &KeyInputWindow::inScaleMode()
{
    return this->m_inScaleMode;
}

bool &KeyInputWindow::iskeyboardActionsLocked()
{
    return this->m_iskeyboardActionsLocked;
}

int &KeyInputWindow::projectionMode()
{
    return this->m_projectionMode;
}

float &KeyInputWindow::mouseX()
{
    return this->m_mouseX;
}

float &KeyInputWindow::mouseY()
{
    return this->m_mouseY;
}
