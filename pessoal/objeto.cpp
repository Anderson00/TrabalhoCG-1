#include "objeto.h"

Objeto::Objeto(string name, std::string instance) : m_nome(name), m_instance(instance)
{

}

void Objeto::desenha()
{
    // T.Rz.Ry.Rx.S (correspondente ao T'' da Q1 da lista 1)
    glTranslatef(t.x,t.y,t.z); //transformacao (matriz) mais a esquerda (mais global)
    glRotatef(a.z,0,0,1);  // \ .
    glRotatef(a.y,0,1,0);  //  | Rz.Ry.Rx . v
    glRotatef(a.x,1,0,0);  // /
    GUI::drawOrigin(1*this->m_drawGizmo);
    glScalef(s.x,s.y,s.z); //transformacao (matriz) mais a direita (mais local)
}

string& Objeto::nome()
{
    return this->m_nome;
}

bool &Objeto::drawGizmo()
{
    return this->m_drawGizmo;
}

string Objeto::instance()
{
    return this->m_instance;
}
