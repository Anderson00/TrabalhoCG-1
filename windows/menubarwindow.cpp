#include "menubarwindow.h"

MenuBarWindow::MenuBarWindow() : Window("")
{

}

void MenuBarWindow::desenhar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            setFileMenu();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void MenuBarWindow::setFileMenu()
{
    if (ImGui::MenuItem("Open", "CTRL+O")) {
        std::cout << "OPEEN";
    }
}
