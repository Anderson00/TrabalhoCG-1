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
    bool &inTransformationMode();
    bool &inTranslateMode();
    bool &inRotationMode();
    bool &inScaleMode();
    bool &iskeyboardActionsLocked();

private:
    unsigned int m_key;
    bool m_inInsertionMode;
    bool m_inTransformationMode;
    bool m_inTranslateMode;
    bool m_inRotationMode;
    bool m_inScaleMode;

    bool m_iskeyboardActionsLocked;
};

#endif // KEYINPUTWINDOW_H
