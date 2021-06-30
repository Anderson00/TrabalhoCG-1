#ifndef INSPECTWINDOW_H
#define INSPECTWINDOW_H

#include "window.h"
#include "hierarchywindow.h"

class InspectWindow : public Window
{
public:
    InspectWindow();

    void desenhar() override;

    HierarchyWindow *hierarchyWindow();
    HierarchyWindow *hierarchyWindow(HierarchyWindow * window);

private:
    HierarchyWindow *m_hierarchyWindow = nullptr;
};

#endif // INSPECTWINDOW_H
