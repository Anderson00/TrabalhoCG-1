#include "novoobjeto.h"

novoObjeto::novoObjeto()
{

}

void novoObjeto::desenha()
{
    glPushMatrix();
        Objeto::desenha();
        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(1,1,0);
        }
        //desenha de fato a modelagem do novo objeto
        GUI::drawBox(0,0,0,1,1,1);
    glPopMatrix();
}
