#ifndef HIERARCHYWINDOW_H
#define HIERARCHYWINDOW_H

#include "window.h"
#include "pessoal/objeto.h"
#include <vector>

class HierarchyWindow : public Window
{
public:
    HierarchyWindow();
    ~HierarchyWindow();

    void desenhar() override;
    std::vector<Objeto *> &objetos();

    void addObjeto(Objeto *obj);
    void removeObjeto(Objeto *obj);
    void removeObjeto(size_t indice);

private:
    std::vector<Objeto*> m_objetos;
};

#endif // HIERARCHYWINDOW_H
