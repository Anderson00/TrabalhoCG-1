#include "hierarchywindow.h"

HierarchyWindow::HierarchyWindow() : Window("Hierarchy", 0, 0, 150, 200)
{
    this->flags() = ImGuiWindowFlags_AlwaysVerticalScrollbar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove;
}

HierarchyWindow::~HierarchyWindow()
{
    for(Objeto* obj : this->m_objetos)
        delete obj;
}

void HierarchyWindow::desenhar()
{
    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::Begin(this->title().c_str(), NULL, this->flags());
    ImGui::SetWindowPos(ImVec2(glutGet(GLUT_WINDOW_WIDTH) -  this->size().x, 19));
    ImGui::SetWindowSize(this->size());

    static const char* listbox_items[255];
    static int listbox_item_current = -1;

    for(size_t i = 0; i < this->m_objetos.size(); i++){
        listbox_items[i] = this->m_objetos[i]->nome().c_str();
        std::cout << listbox_items[i] << std::endl;
    }


    ImGui::ListBox("", &listbox_item_current, listbox_items, this->m_objetos.size(), 10);
    memset(listbox_items, 0, 255);

    ImGui::End();
}

std::vector<Objeto *> &HierarchyWindow::objetos()
{
    return this->m_objetos;
}

void HierarchyWindow::addObjeto(Objeto *obj)
{
    this->m_objetos.push_back(obj);
}

void HierarchyWindow::removeObjeto(Objeto *obj)
{
    size_t contador = -1;
    for(size_t i = 0; i < this->m_objetos.size(); i++){
        if(obj == this->m_objetos[i]){
            contador = i;
        }
    }
    if(contador >= 0){
        removeObjeto(contador);
    }
}

void HierarchyWindow::removeObjeto(size_t indice)
{
    if(indice < this->m_objetos.size()){
        Objeto *obj = this->m_objetos[indice];
        delete obj;

        this->m_objetos.erase(this->m_objetos.begin()+indice);
    }
}
