#ifndef MENUBARWINDOW_H
#define MENUBARWINDOW_H

#include "window.h"
#include "hierarchywindow.h"
#include "utils/filecontroller.h"

class MenuBarWindow : public Window
{
public:
    MenuBarWindow();

    void desenhar() override;

    FileController *fileController();
    FileController *fileController(FileController *controller);

    HierarchyWindow *hierarchyWindow();
    HierarchyWindow *hierarchyWindow(HierarchyWindow *objetos);

private:
    void setFileMenu();
    void setHelpMenu();

    FileController *m_fileController;
    HierarchyWindow *m_hierarchyWindow;
};

#endif // MENUBARWINDOW_H
