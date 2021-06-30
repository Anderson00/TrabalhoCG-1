#include "objectfile.h"

ObjectFile::ObjectFile(std::string fileDir)
{
    this->m_model = new Model3DS(fileDir.c_str());
}

void ObjectFile::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        GUI::setColor(0.5,0.5,0.5);

        if (selecionado) {
            GUI::drawBox(-1,-1,-1, 1,1,1, true);
        }

        glScalef(1,1,1.2);
        glRotatef(-90,1,0,0);
        glTranslatef(0,0,0);
        glScalef(0.001,0.001,0.001);
        this->m_model->draw(!selecionado);
    glPopMatrix();

}

Model3DS *ObjectFile::model()
{
    return this->m_model;
}

Model3DS *ObjectFile::model(Model3DS *model)
{
    m_model = model;
    return m_model;
}
