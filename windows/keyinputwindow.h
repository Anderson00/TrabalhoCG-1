#ifndef KEYINPUTWINDOW_H
#define KEYINPUTWINDOW_H

#include "window.h"

class KeyInputWindow : public Window
{
public:
    KeyInputWindow();

    void desenhar() override;

    unsigned int &key();

    bool &inInsertionMode();
    bool &inTranslateMode();
    bool &inRotationMode();
    bool &inScaleMode();

private:
    unsigned int m_key;
    bool m_inInsertionMode;
    bool m_inTranslateMode;
    bool m_inRotationMode;
    bool m_inScaleMode;
};

#endif // KEYINPUTWINDOW_H
