#include <iostream>

using namespace std;

//#include <gui.h>
#include <vector>
#include <QApplication>

//imgui includes
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glut.h"
#include "imgui/examples/imgui_impl_opengl2.h"

//#include <objeto.h>
#include <personagem.h>
#include <casa.h>
#include <carro.h>
#include <novoobjeto.h>

//Windows
#include "windows/menubarwindow.h"
#include "windows/keyinputwindow.h"
#include "windows/hierarchywindow.h"
#include "windows/inspectwindow.h"
#include "windows/assetswindow.h"

//File
#include "utils/filecontroller.h"

// Our state
static bool show_demo_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

KeyInputWindow inputWindow;
HierarchyWindow hierarchyWindow;
InspectWindow inspectWindow;
MenuBarWindow menubar;
AssetsWindow assetsWindow;

vector<Objeto*> &objetos = hierarchyWindow.objetos();
int &posSelecionado = hierarchyWindow.itemIndiceSelected();

//-------------------sombra-------------------
bool drawShadow = true;
bool pontual = true;
float k = 0.0;
//-------------------sombra-------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();
void desenhaPontosDeControle();

//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport auxiliar sobrepondo a principal
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
//        Vetor3D eye = pontosControle[4];
//        Vetor3D center = pontosControle[2];
//        gluLookAt(eye.x,eye.y,eye.z, center.x,center.y,center.z, 0.0,1.0,0.0);
            cenario();
}
//-------------------viewPorts------------------

void cenario() {
    //GUI::setLight(1,1,3,5,true,false);               //multiplas fontes de luz
    //GUI::setLight(2,-1.5,0.5,-1,true,false);         //multiplas fontes de luz
    GUI::setLight(3,-5,3,5,true,false);
    //GUI::setLight(3,-5,3,5,true,true); //atenuada
    //GUI::setLight(3,-5,3,5,true,false,false,false,true,true); //spot (holofote, lanterna)

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
    GUI::setColor(0,0,0);
    Desenha::drawGrid( 5, 0, 1, 1 );

    desenhaPontosDeControle();
}


//-------------------picking------------------
vector<Vetor3D> pontosControle;

int pontoSelecionado = 0; //names = [1,n] //n = pontosControle.size()
//bool transPontos = glutGUI::trans_obj; //= true;

void desenhaPontosDeControle()
{
    for (int i=0; i<objetos.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado-1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,0,1,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Objeto *p = objetos[i];
        glPushName(i+1); //não se deve definir name = 0!
            //GUI::drawSphere(p.x,p.y,p.z,0.2);

            p->desenha();
            if(i == pontoSelecionado - 1)
                p->drawGizmo() = true;
            else
                p->drawGizmo() = false;
            GUI::setColor(1,0,0,1, true);
        glPopName();
    }

}

void imgui_display()
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    menubar.desenhar();
    inputWindow.desenhar();
    hierarchyWindow.desenhar();
    inspectWindow.desenhar();
    assetsWindow.desenhar();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Stats", NULL);

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

Vetor3D transformedPoint(Vetor3D p)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRotatef(objetos[0]->a.z,0,0,1);  // \ .
    glRotatef(objetos[0]->a.y,0,1,0);  //  | Rz.Ry.Rx . v
    glRotatef(objetos[0]->a.x,1,0,0);

    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();

    float pos[4] = {p.x,p.y,p.z, 1.0};
    float res[4];

    glutGUI::multGLMatrixByVector(res,matrix,pos);

    Vetor3D res3D = Vetor3D(res[0],res[1],res[2]);
    return res3D;
}

void displayInner() {
    GUI::setLight(1,1,3,5,true,false);
    GUI::setLight(2,-1.5,0.5,-1,true,false);
    //GUI::setLight(3,-5,3,5,true,false);
    Objeto *floor = nullptr;

    GUI::drawOrigin(1);

    GUI::setColor(1,0,0);
    //GUI::drawFloor();

    desenhaPontosDeControle();

//    for (int i = 0; i < objetos.size(); ++i) {
//        glPushMatrix();
//            objetos[i]->desenha();
//        glPopMatrix();

//        if(objetos[i]->nome() == "chao"){
//            floor = objetos[i];
//            floor->shadowVisible() = false;
//        }
//    }



    //-------------------sombra-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos[4] = {-1+glutGUI::lx,2+glutGUI::ly,1+glutGUI::lz, pontual};
    if(floor != nullptr){
        k = floor->t.y + 0.01;
    }
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,-1,2,1,true,false,false,false, pontual);
    //desenhando os objetos projetados
    glPushMatrix();
        //matriz p multiplicar tudo por -1
            //float neg[16] = {
            //                   -1.0, 0.0, 0.0, 0.0,
            //                    0.0,-1.0, 0.0, 0.0,
            //                    0.0, 0.0,-1.0, 0.0,
            //                    0.0, 0.0, 0.0,-1.0
            //                };
            //glMultTransposeMatrixf( neg );
        //matriz de projecao para gerar sombra no plano y=k
            GLfloat sombra[4][4];
            GUI::shadowMatrixYk(sombra,lightPos,k);
            //GLfloat plano[4] = {0,1,0,-k};
            //GUI::shadowMatrix(sombra,plano,lightPos);
            glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {
                if(objetos[i]->shadowVisible()){
                    glPushMatrix();
                        objetos[i]->desenha();
                    glPopMatrix();
                }
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
        //glDisable(GL_LIGHTING);
        //glColor3d(0.0,0.0,0.0);
        //if (drawShadow) desenhaObjetosComSombra();
        //glEnable(GL_LIGHTING);
    glPopMatrix();
    //-------------------sombra-------------------
}

void desenha() {
    GUI::displayInit();

    // Start the Dear ImGui frame

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    imgui_display();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);

    displayInner();

    GUI::setColor(clear_color.x, clear_color.y, clear_color.z, 1);
    //GUI::drawSphere(1, 1, 0, 0.5);

    if (!objetos.empty()) {
        glLoadIdentity();
        glViewport(0, 3*glutGUI::height/4, glutGUI::width/4, glutGUI::height/4);
        Vetor3D zlocalemCoordsGlobais = transformedPoint(Vetor3D(0,0,1));
        Vetor3D olho = objetos[0]->t + zlocalemCoordsGlobais*1.2;
        Vetor3D centro = olho + zlocalemCoordsGlobais;

        Vetor3D ylocalemCoordsGlobais = transformedPoint(Vetor3D(0,1,0));
        Vetor3D up = ylocalemCoordsGlobais;

        gluLookAt(olho.x,olho.y,olho.z, centro.x,centro.y,centro.z, up.x,up.y,up.z);
        displayInner();
    }

    //transladando ponto selecionado atraves do picking
       //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
       if (pontoSelecionado!=0) {
           pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
           pontosControle[pontoSelecionado-1].y += glutGUI::dty;
           pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
       }



    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }


    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    //glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());



    GUI::displayEnd();
    glutPostRedisplay();
}

bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    inputWindow.key() = key;

    if(ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)){
        ImGui_ImplGLUT_KeyboardFunc(key, x, y);
        inputWindow.iskeyboardActionsLocked() = true;
        return;
    }
    inputWindow.iskeyboardActionsLocked() = false;
    GUI::keyInit(key,x,y);

    inputWindow.key() = key;

    switch (key) {
    case 't':
        inputWindow.inTransformationMode() = glutGUI::trans_obj = !glutGUI::trans_obj;
        if(glutGUI::trans_obj == false)
            glutGUI::clearModes();
        break;
    case 'l':
        inputWindow.inTransformationMode() = glutGUI::trans_luz = !glutGUI::trans_luz;
        if(glutGUI::trans_obj == false)
            glutGUI::clearModes();
        break;
    case 'n':
        if(objetos.size() == 0)
            break;
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado++;
        posSelecionado = posSelecionado%objetos.size();
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case 'b':
        if(objetos.size() == 0)
            break;
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado--;
        if (posSelecionado < 0) {
            posSelecionado = objetos.size()-1;
        }
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case '\'':{
        if(hierarchyWindow.itemIndiceSelected() >= 0){
            float eyeX = glutGUI::cam->e.x;
            float eyeY = glutGUI::cam->e.y;
            float eyeZ = glutGUI::cam->e.z;
            delete glutGUI::cam;
            int index = hierarchyWindow.itemIndiceSelected();
            glutGUI::cam = new CameraDistante(Vetor3D(eyeX, eyeY, eyeZ),
                                              Vetor3D(objetos[index]->t.x, objetos[index]->t.y, objetos[index]->t.z),
                                              Vetor3D(0,1,0));
        }
    }
        break;


    case 'O':
        inputWindow.inInsertionMode() = incluirObjeto = !incluirObjeto;
        break;
    case 'p':
        if (incluirObjeto) {
            objetos.push_back( new Personagem("Player") );
        }
        break;
    case 'c':
        if (incluirObjeto) {
            objetos.push_back( new Carro() );
        }
        break;
    case 'C':
        if (incluirObjeto) {
            objetos.push_back( new Casa() );
        }
        break;
    case '4':
        if (incluirObjeto) {
            objetos.push_back( new novoObjeto() );
        }
        break;
    case 'i':
        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
            objetos[posSelecionado]->t.x = 0.0;
            objetos[posSelecionado]->t.y = 0.0;
            objetos[posSelecionado]->t.z = 0.0;

            objetos[posSelecionado]->a.x += glutGUI::dax;
            objetos[posSelecionado]->a.y += glutGUI::day;
            objetos[posSelecionado]->a.z += glutGUI::daz;

            objetos[posSelecionado]->s.x += glutGUI::dsx;
            objetos[posSelecionado]->s.y += glutGUI::dsy;
            objetos[posSelecionado]->s.z += glutGUI::dsz;
        }
        break;

    default:
        break;
    }
}



//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

void mouse(int button, int state, int x, int y) {
    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                posSelecionado = pontoSelecionado - 1;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main(int argc, char **argv)
{

    int n = 5;
    float dist = 1.0;
    for (int i=0; i<n; i++) {
        pontosControle.push_back( Vetor3D((i-n/2)*dist,1,0) );
    }

    GUI::onProjectionChange = new std::function([&](int pespIndex) {
       if(pespIndex >= 0){
           inputWindow.projectionMode() = pespIndex;
       }
    });

    FileController controller;
    glutGUI::modes[0] = &inputWindow.inTranslateMode();
    glutGUI::modes[1] = &inputWindow.inRotationMode();
    glutGUI::modes[2] = &inputWindow.inScaleMode();
    inspectWindow.hierarchyWindow(&hierarchyWindow);
    assetsWindow.hierarchyWindow(&hierarchyWindow);
    assetsWindow.inspectWindow(&inspectWindow);
    assetsWindow.fileController(&controller);

    menubar.fileController(&controller);
    menubar.hierarchyWindow(&hierarchyWindow);

    QApplication app(argc, argv);
    GUI gui = GUI(800,600,desenha,teclado, mouse);
    return app.exec();
}
