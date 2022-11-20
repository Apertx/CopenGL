#include "main.h"
#include "texture.h"
#include "wrap_wnd.h"
#include <windows.h>
#include "GL.h"
#include "GLU.h"

#define X0 0.0f
#define X1 1.0f / 3.0f
#define X2 2.0f / 3.0f
#define X3 1.0f
#define Y0 0.0f
#define Y1 0.5f
#define Y2 1.0f

float f = 0.4f;

float textures[6][4][2] = {
    X0, Y0, X1, Y0, X1, Y1, X0, Y1,
    X1, Y0, X2, Y0, X2, Y1, X1, Y1,
    X2, Y0, X3, Y0, X3, Y1, X2, Y1,
    X0, Y1, X1, Y1, X1, Y2, X0, Y2,
    X1, Y1, X2, Y1, X2, Y2, X1, Y2,
    X2, Y1, X3, Y1, X3, Y2, X2, Y2,
};

float cube[6][4][3] = {
    -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
    -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
    -1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,
    -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1,
    -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
    1, -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1,
};


void myInit(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    loadTexture("resources/tex01.bmp");
    loadTexture("resources/tex02.bmp");
    loadTexture("resources/tex03.bmp");
    loadTexture("resources/tex04.bmp");

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glBindTexture(GL_TEXTURE_2D, 1);
    myResize(APP_WIDTH, APP_HEIGHT);
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(30.0f, 1.0f, 1.0f, 1.0f);
}

void myResize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glScalef(0.3f, ratio * 0.3f, 0.3f);
    glMatrixMode(GL_MODELVIEW);
}

void myDraw(void) {
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    for (i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        for (j = 0; j < 4; j++) {
            glTexCoord2f(textures[i][j][0], textures[i][j][1]);
            glVertex3f(cube[i][j][0], cube[i][j][1], cube[i][j][2]);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
    glRotatef(f, 1.0, 1.0, 1.0);
}

void myKeyDown(int key) {
    switch (key) {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    case VK_UP:
        f += 0.1;
        break;
    case VK_DOWN:
        f -= 0.1;
        break;
    case '1':
        glBindTexture(GL_TEXTURE_2D, 1);
        break;
    case '2':
        glBindTexture(GL_TEXTURE_2D, 2);
        break;
    case '3':
        glBindTexture(GL_TEXTURE_2D, 3);
        break;
    case '4':
        glBindTexture(GL_TEXTURE_2D, 4);
        break;
    }
}

void myKeyUp(int key) {
    switch (key) {
    }
}
