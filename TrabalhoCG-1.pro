TEMPLATE = app
CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += pessoal

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    pessoal/casa.cpp \
    pessoal/personagem.cpp \
    pessoal/objeto.cpp \
    pessoal/carro.cpp \
    pessoal/novoobjeto.cpp \
    imgui/imgui.cpp \
    imgui/imgui_demo.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_widgets.cpp \
    imgui/examples/imgui_impl_glut.cpp \
    imgui/examples/imgui_impl_opengl2.cpp \
    windows/assetswindow.cpp \
    windows/hierarchywindow.cpp \
    windows/keyinputwindow.cpp \
    windows/menubarwindow.cpp \
    windows/window.cpp


HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    pessoal/casa.h \
    pessoal/personagem.h \
    pessoal/objeto.h \
    pessoal/carro.h \
    pessoal/novoobjeto.h \
    imgui/imgui.h \
    imgui/imgui_demo.h \
    imgui/imgui_draw.h \
    imgui/imgui_widgets.h \
    imgui/examples/imgui_impl_glut.h \
    windows/assetswindow.h \
    windows/hierarchywindow.h \
    windows/keyinputwindow.h \
    windows/menubarwindow.h \
    windows/window.h
    imgui/examples/imgui_impl_opengl2.h
