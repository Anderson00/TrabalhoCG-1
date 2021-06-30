#include "hierarchywindow.h"

HierarchyWindow::HierarchyWindow() : Window("Hierarchy", 0, 0, 250, 200)
{
    this->flags() = ImGuiWindowFlags_AlwaysVerticalScrollbar |
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
    this->isCollpased() = ImGui::IsWindowCollapsed();

    static bool selection[255] = {false};

    for(size_t i = 0; i < this->m_objetos.size(); i++){
        if(ImGui::Selectable(std::string(std::to_string(i)).append(" ").append(this->m_objetos[i]->nome()).c_str(), &selection[i])){
            m_itemIndiceSelected = i;
        }
        if(m_itemIndiceSelected == i)
            this->m_objetos[i]->selecionado = true;
        else
            this->m_objetos[i]->selecionado = false;

    }

    memset(selection, false, 255);
    selection[m_itemIndiceSelected] = true;

    ImGui::End();
}

std::vector<Objeto *> &HierarchyWindow::objetos()
{
    return this->m_objetos;
}

void HierarchyWindow::replaceObjetos(std::vector<Objeto *> objetos)
{
    this->clearAll();
    this->m_objetos = objetos;
}

int &HierarchyWindow::itemIndiceSelected()
{
    return this->m_itemIndiceSelected;
}

void HierarchyWindow::addObjeto(Objeto *obj)
{
    if(obj != nullptr)
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

void HierarchyWindow::clearAll()
{
    for(Objeto *obj : this->m_objetos){
        delete obj;
    }

    this->m_objetos.clear();
    this->m_itemIndiceSelected = -1;
}
