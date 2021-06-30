#ifndef ASSETSWINDOW_H
#define ASSETSWINDOW_H

#include "window.h"
#include "hierarchywindow.h"
#include "inspectwindow.h"
#include "utils/filecontroller.h"

class AssetsWindow  : public Window
{
public:
    AssetsWindow();

    void desenhar() override;

    HierarchyWindow *hierarchyWindow();
    HierarchyWindow *hierarchyWindow(HierarchyWindow *window);

    InspectWindow *inspectWindow();
    InspectWindow *inspectWindow(InspectWindow *window);

    FileController *fileController();
    FileController *fileController(FileController *controller);

private:
    HierarchyWindow *m_hierarchyWindow;
    InspectWindow *m_inspectWindow;
    FileController *m_fileController;
};

#endif // ASSETSWINDOW_H
