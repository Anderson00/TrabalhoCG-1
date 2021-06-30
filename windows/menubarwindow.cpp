#include "menubarwindow.h"
#include <QMainWindow>
#include <QFileDialog>
#include <vector>

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

FileController *MenuBarWindow::fileController()
{
    return this->m_fileController;
}

FileController *MenuBarWindow::fileController(FileController *controller)
{
    this->m_fileController = controller;
    return this->m_fileController;
}

HierarchyWindow *MenuBarWindow::hierarchyWindow()
{
    return this->m_hierarchyWindow;
}

HierarchyWindow *MenuBarWindow::hierarchyWindow(HierarchyWindow *objetos)
{
    this->m_hierarchyWindow = objetos;
    return this->m_hierarchyWindow;
}

void MenuBarWindow::setFileMenu()
{
    if (ImGui::MenuItem("Open Scene", "CTRL+O")) {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Abrir", "./", "Files (*.csv)");
        if(!fileName.isEmpty()){
            this->m_hierarchyWindow->clearAll();
            this->m_hierarchyWindow->objetos() = this->m_fileController->openScene(fileName.toStdString());
        }
    }

    if (ImGui::MenuItem("Save", NULL, false, this->m_hierarchyWindow->objetos().size() > 0)) {
        //QFileDialog::getOpenFileName(nullptr, "Abrir", "./", "Image Files (*.cfg)");

        this->m_fileController->saveScene(this->m_hierarchyWindow->objetos());
    }
}
