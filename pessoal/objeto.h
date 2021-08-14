#ifndef OBJETO_H
#define OBJETO_H

#include <gui.h>

class Objeto
{
public:
    Vetor3D t = Vetor3D(0,0,0);
    Vetor3D a = Vetor3D(0,0,0);
    Vetor3D s = Vetor3D(1,1,1);
    float m_r , m_g, m_b, m_alp;
    bool selecionado = false;

    Objeto(std::string nome = "<sem nome>", std::string instance = "primitivo");
    virtual void desenha();

    std::string &nome();
    bool &drawGizmo();
    bool &shadowVisible();
    std::string instance();

    void setColor(float r, float g, float b, float alph);
    float &r();
    float &g();
    float &b();
    float &alp();


private:
    std::string m_nome;
    bool m_drawGizmo = false;
    bool m_shadowVisible = false;
    //float m_r , m_g, m_b, m_alp;
    std::string m_instance;
};

#endif // OBJETO_H
