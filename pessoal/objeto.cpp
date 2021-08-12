#include "objeto.h"

Objeto::Objeto(string name, std::string instance) : m_nome(name), m_instance(instance)
{
    this->m_r = 0.5;
    this->m_g = 0.5;
    this->m_b = 0.5;
    this->m_alp = 1;
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
    GUI::setColor(this->m_r, this->m_g, this->m_b, this->m_alp);
}

string& Objeto::nome()
{
    return this->m_nome;
}

bool &Objeto::drawGizmo()
{
    return this->m_drawGizmo;
}

bool &Objeto::shadowVisible()
{
    return this->m_shadowVisible;
}

string Objeto::instance()
{
    return this->m_instance;
}

void Objeto::setColor(float r, float g, float b, float alph)
{
    this->m_r = r;
    this->m_g = g;
    this->m_b = b;
    this->m_alp = alph;
}

float &Objeto::r()
{
    return this->m_r;
}

float &Objeto::g()
{
    return this->m_g;
}

float &Objeto::b()
{
    return this->m_b;
}

float &Objeto::alp()
{
    return this->m_alp;
}
