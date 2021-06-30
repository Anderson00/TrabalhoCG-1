#include "objetoprimitivo.h"

ObjetoPrimitivo::ObjetoPrimitivo(std::string tipo) : Objeto("<Primitivo>", "primitivo"), m_tipo(tipo)
{

}

void ObjetoPrimitivo::desenha()
{
    glPushMatrix();
        Objeto::desenha();
        GUI::setColor(0.5, 0.5, 0.5, 1);
        if(this->m_tipo == "Box"){
           GUI::drawBox(-0.5,0.0,-0.5, 0.5,0.5,0.5);
        }else if(this->m_tipo == "Sphere"){
            GUI::drawSphere(1, 1, 0, 0.5);
        }else if(this->m_tipo == "Floor"){
            GUI::drawFloor();
        }else if(this->m_tipo == "Square"){
            GUI::drawQuad();
        }
    glPopMatrix();
}

string ObjetoPrimitivo::tipo()
{
    return this->m_tipo;
}
