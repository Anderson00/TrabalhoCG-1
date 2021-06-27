#ifndef MENUBARWINDOW_H
#define MENUBARWINDOW_H

#include "window.h"

class MenuBarWindow : public Window
{
public:
    MenuBarWindow();

    void desenhar() override;
private:
    void setFileMenu();
};

#endif // MENUBARWINDOW_H
