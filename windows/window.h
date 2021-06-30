#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "gui_glut/gui.h"
#include "gui_glut/extra.h"
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glut.h"
#include "imgui/examples/imgui_impl_opengl2.h"


class Window
{
public:
    Window(std::string title, float x, float y, float width, float height);
    Window(std::string title, float width, float height);
    Window(std::string title);

    virtual void desenhar() = 0;

    std::string title();
    ImVec2 &position();
    ImVec2& size();
    ImGuiWindowFlags& flags();
    bool &isCollpased();
private:
    std::string m_title;
    ImVec2 m_pos;
    ImVec2 m_size;
    ImGuiWindowFlags m_flags;
    bool m_isCollpased;
};

#endif // WINDOW_H
