#ifndef OBJETOPRIMITIVO_H
#define OBJETOPRIMITIVO_H

#include "objeto.h"

class ObjetoPrimitivo : public Objeto
{
public:
    ObjetoPrimitivo(std::string tipo);

    void desenha() override;

    std::string tipo();

private:
    std::string m_tipo;
};

#endif // OBJETOPRIMITIVO_H
