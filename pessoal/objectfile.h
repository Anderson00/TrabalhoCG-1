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

    std::string fileName();

private:
     Model3DS* m_model;
     std::string fileDir;
};

#endif // OBJECTFILE_H
