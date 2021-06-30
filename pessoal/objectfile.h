#ifndef OBJECTFILE_H
#define OBJECTFILE_H


#include "objeto.h"

class ObjectFile : public Objeto
{
public:
    ObjectFile(std::string fileDir);
    void desenha() override;

    Model3DS *model();
    Model3DS *model(Model3DS *model);

private:
     Model3DS* m_model;
};

#endif // OBJECTFILE_H
