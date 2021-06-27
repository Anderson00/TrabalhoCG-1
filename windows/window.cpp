#include "window.h"


Window::Window(std::string title, float x, float y, float width, float height) : m_title(title), m_pos(x, y), m_size(width, height)
{

}

Window::Window(std::string title, float width, float height) : Window(title, 0, 0, width, height)
{

}

Window::Window(std::string title) : Window(title, 0, 0, 0, 0)
{
    this->m_flags = ImGuiWindowFlags_AlwaysAutoResize;
}

std::string Window::title()
{
    return this->m_title;
}

ImVec2& Window::position()
{
    return this->m_pos;
}

ImVec2& Window::size()
{
    return this->m_size;
}

ImGuiWindowFlags& Window::flags()
{
    return this->m_flags;
}
