#ifndef BEZIERWINDOW_H
#define BEZIERWINDOW_H

#include "window.h"
#include "hierarchywindow.h"
#include "inspectwindow.h"
#include "utils/filecontroller.h"
//#include "utils/bezier.h"

class BezierWindow  : public Window
{
public:
    BezierWindow();

   float *p0, *p1, *p2, *p3;

    void desenhar() override;

private:

};

#endif // BEZIERWINDOW_H
