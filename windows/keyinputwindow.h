#ifndef KEYINPUTWINDOW_H
#define KEYINPUTWINDOW_H

#include "window.h"

class KeyInputWindow : public Window
{
public:
    KeyInputWindow();

    void desenhar() override;

    unsigned int &key();

private:
    unsigned int m_key;
};

#endif // KEYINPUTWINDOW_H
