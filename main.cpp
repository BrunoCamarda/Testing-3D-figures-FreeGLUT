// Visualizaçao 3D
// Desenha um cubo centrado na origem com faces de -1 a 1
// coloridas com diferentes cores
//
// Permite que a posicao do observador seja alterada usando o teclado
// X -> soma uma unidade na coordenada x do observador
// x -> subtrai  uma unidade na coordenada x do observador
// Y -> soma uma unidade na coordenada y do observador
// y -> subtrai  uma unidade na coordenada y do observador
// Z -> soma uma unidade na coordenada z do observador
// z -> subtrai  uma unidade na coordenada z do observador
//
// Marcus V. A. Andrade - 25/09/2008 - Modificado por Thiago Luange Gomes
// Usado como exercício prático por Bruno Araujo Camarda

#include <GL/gl.h>
#include <GL/glut.h>

#include <stdlib.h>
int FIGURE=0;
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

void colorcube();

//tamanho da janela em pixels
int largurajanela = 600, alturajanela = 500;

//vertices do cubo
GLfloat vertices[10][3] = { {-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0}, {0, 2.5, 0}, {0, -2.5, 0}
};


//cor de cada face do cubo
GLfloat colors[6][3] = { {0.0,0.0,0.0} , {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
    {0.0,0.0,1.0} , {1.0,0.0,1.0}
};

//posicao do observador (camera)
GLdouble viewer[] = {4.0, 4.0, 6.0};

// desenha uma face do cubo
// a, b, c e d sao indices no vetor de vertices
// ncolor eh um indice no vetor de cores
void quad(int a, int b, int c, int d, int ncolor)
{
    glColor3fv(colors[ncolor]);
    glBegin(GL_QUADS);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}


void tri(int a, int b, int c, int ncolor)
{
    glColor3fv(colors[ncolor]);
    glBegin(GL_TRIANGLES);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glEnd();
}

//desenha o cubo (faces no sentido anti-horario - face externa)
void colorcube()
{
    quad(1,2,3,0,0); //frente
    quad(6,7,3,2,1); //lado direito
    quad(3,7,4,0,2); //baixo
    quad(5,6,2,1,3); //cima
    quad(7,6,5,4,4); //traz
    quad(4,5,1,0,5); //lado esquerdo

}

void colorpyramid()
{
    quad(5,6,2,1,3); //base
    tri(8,6,2,0);
    tri(8,5,6,1);
    tri(8,2,1,2);
    tri(8,1,5,5);

}

void colorcube_with_pyramid_top(){
    quad(1,2,3,0,0); //frente
    quad(6,7,3,2,1); //lado direito
    quad(3,7,4,0,2); //baixo
    quad(5,6,2,1,3); //cima
    quad(7,6,5,4,4); //traz
    quad(4,5,1,0,5); //lado esquerdo

    tri(8,6,2,2);
    tri(8,5,6,1);
    tri(8,2,1,6);
    tri(8,1,5,3);

    tri(9,3,7,0);
    tri(9,7,4,2);
    tri(9,4,0,1);
    tri(9,0,3,3);

}

void MenuPrincipal(int op)
{

    switch(op)
    {
    case 0:
        FIGURE = 0;
        break;
    case 1:
        FIGURE = 1;
        break;
    case 2:
        FIGURE = 2;
        break;

    }

    glutPostRedisplay();
}



void CriaMenu()
{
    int menu;

    // Cria menu principal...
    menu = glutCreateMenu(MenuPrincipal);
    // ... e adiciona ambos submenus a ele
    glutAddMenuEntry("Cubo",0);
    glutAddMenuEntry("Piramide",1);
    glutAddMenuEntry("Estrela",2);

    // Associa o menu ao botão direito do mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
// define o tipo de projecao
// glOrtho(left, right, bottom, top, near, far) -> projecao paralela
// glFrustum(left, right, bottom, top, near, far) -> projecao perspectiva
// gluPerspective(viewAngle, aspectRatio, near, far) -> projecao perspectiva
void init(void)
{
    CriaMenu();
    glClearColor(1.0, 1.0, 1.0, 1.0); // cor para limpeza do buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0); // projeção paralela

    //glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0); // projeção perspectiva

    gluPerspective(35.0,1.0,2.0,100.0); // projeção perspectiva
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a janela
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2], // define posicao do observador
              0.0, 0.0, 0.0,                           // ponto de interesse (foco)
              0.0, 1.0, 0.0);                          // vetor de "view up"
    if(FIGURE == 0)
    {
        glLoadIdentity();
        gluLookAt(viewer[0],viewer[1],viewer[2], // define posicao do observador
                  0.0, 0.0, 0.0,                           // ponto de interesse (foco)
                  0.0, 1.0, 0.0);
        colorcube(); //desenha o cubo
    }

    if (FIGURE == 1){
        glLoadIdentity();
        gluLookAt(viewer[0],viewer[1],viewer[2], // define posicao do observador
                  0.0, 1.0, 0.0,                           // ponto de interesse (foco)
                  0.0, 1.0, 0.0);
        colorpyramid(); //desenha a piramide
    }

    if (FIGURE == 2){
        glLoadIdentity();
        gluLookAt(viewer[0],viewer[1],viewer[2], // define posicao do observador
                  0.0, 0.0, 0.0,                           // ponto de interesse (foco)
                  0.0, 1.0, 0.0);
        colorcube_with_pyramid_top(); //desenha a piramide
    }


    glFlush();
    glutSwapBuffers(); //usando double buffer (para evitar 'flicker')
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) exit(0); //ESC
    if (key == 'x') viewer[0] -= 1.0;
    if (key == 'X') viewer[0] += 1.0;
    if (key == 'y') viewer[1] -= 1.0;
    if (key == 'Y') viewer[1] += 1.0;
    if (key == 'z') viewer[2] -= 1.0;
    if (key == 'Z') viewer[2] += 1.0;
    display();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv); //inicializa a glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //tipo de buffer/cores
    glutInitWindowSize(largurajanela, alturajanela); //dimensões da janela
    glutInitWindowPosition(100, 100); //posicao da janela
    glutCreateWindow("Visualizacao 3D - Movimento de camera "); //cria a janela
    init();
    glutDisplayFunc(display); //determina função callback de desenho
    glutKeyboardFunc(keyboard); //determina função callback de teclado
    glEnable(GL_DEPTH_TEST); //habilita remoção de superfícies ocultas
    glutMainLoop();
    return 0;
}
